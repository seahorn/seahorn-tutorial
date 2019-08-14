import sys
import z3

class HtmlStr(object):
    def __init__(self, s):
        self._s = s

    def _repr_html_(self):
        return self._s

    def __repr__(self):
        return repr(self._s)
    def __str__(self):
        return str(self._s)

class Ts(object):
    def __init__(self, name='Ts'):
        # string name
        self._name = name
        # state variables (pair of input and output)
        self._vars = []
        # inputs
        self._inputs = []

        # a map from optional names to state variables
        self._named_vars = dict()
        # Transition relation
        self.Tr = z3.BoolVal(True)
        # Initial condition
        self.Init = z3.BoolVal(True)
        # Bad states
        self.Bad = z3.BoolVal(False)


    def add_var(self, sort, name=None):
        '''Add a state variable of a given sort. Returns a pair (pre, post)
           of a pre- and post- state versions of the variable
        '''
        pre, post = self._new_var_name()
        v_in = z3.Const(pre, sort)
        v_out = z3.Const(post, sort)
        self._vars.append((v_in, v_out))
        if name is not None:
            self._named_vars[name] = (v_in, v_out)

        return (v_in, v_out)

    def get_var(self, idx):
        if isinstance(idx, int):
            return self._vars[idx]
        elif idx in self._named_vars:
            return self._named_vars[idx]
        return None

    def get_pre_var(self, idx):
        res = self.get_var(idx)
        if res is not None:
            return res[0]
        return None

    def get_pre_vars(self, vars):
        return (self.get_pre_var(v) for v in vars.split())

    def get_post_var(self, idx):
        res = self.get_var(idx)
        if res is not None:
            return res[1]
        return None

    def add_input(self, sort):
        '''Add an input of a given sort'''
        v = z3.Const(self._new_input_name(), sort)
        self._inputs.append(v)
        return v

    def inputs(self):
        return self._inputs
    def pre_vars(self):
        return [u for (u, v) in self._vars]
    def post_vars(self):
        return [v for (u, v) in self._vars]
    def vars(self):
        return self.pre_vars() + self.post_vars()
    def all(self):
        return self.vars() + self.inputs()
    def sig(self):
        return [v.sort() for (u, v) in self._vars]
    def to_post(self, e):
        '''Rename expression over pre-state variables to post-state variables'''
        return z3.substitute(e, *self._vars)

    def _new_input_name(self):
        return self._mk_input_name(len(self._inputs))
    def _mk_input_name(self, idx):
        return 'i_' + str(idx)

    def _new_var_name(self):
        idx = len(self._vars)
        return self._mk_var_name(idx), self._mk_post_var_name(idx)

    def _mk_var_name(self, idx):
        return 'v_' + str(idx)
    def _mk_post_var_name(self, idx):
        return 'v_out_' + str(idx)

    def __repr__(self):
        return 'Transition System: ' + self._name + '\n' + \
            '\tInit: ' + str(self.Init) + '\n' + \
            '\tBad: ' + str(self.Bad) + '\n' + \
            '\tTr: ' + str(self.Tr)

    def __str__(self):
        return repr(self)

def vc_gen(T):
    '''Verification Condition (VC) for an Inductive Invariant'''
    Inv = z3.Function('Inv', *(T.sig() + [z3.BoolSort()]))

    InvPre = Inv(*T.pre_vars())
    InvPost = Inv(*T.post_vars())

    all_vars = T.all()
    vc_init = z3.ForAll(all_vars, z3.Implies(T.Init, InvPre))
    vc_ind = z3.ForAll(all_vars, z3.Implies(z3.And(InvPre, T.Tr), InvPost))
    vc_bad = z3.ForAll(all_vars, z3.Implies(z3.And(InvPre, T.Bad), z3.BoolVal(False)))
    return [vc_init, vc_ind, vc_bad], InvPre

def vc_gen_bwd(T):
    '''Verification Condition (VC) for Backward Inductive Invariant'''

    # create predicate Inv
    Inv = z3.Function('BwdInv', *(T.sig() + [z3.BoolSort()]))

    InvPre = Inv(*T.pre_vars())
    InvPost = Inv(*T.post_vars())

    all_vars = T.all()
    vc_init = z3.ForAll(all_vars, z3.Implies(T.Bad, InvPre))
    vc_ind = z3.ForAll(all_vars, z3.Implies(z3.And(InvPost, T.Tr), InvPre))
    vc_bad = z3.ForAll(all_vars, z3.Implies(z3.And(InvPre, T.Init), z3.BoolVal(False)))

    return [vc_init, vc_ind, vc_bad], InvPre

class CFA(object):
    '''Control Flow Automaton -- An automation whose nodes are annotated with transition relations'''
    def __init__(self, name):
        self._base = Ts(name)

        self.entry = None
        self.exit = None
        self.edges = dict()
        self.nodes = set()

    def sig(self):
        return self._base.sig()
    def inputs(self):
        return self._base.inputs()
    def pre_vars(self):
        return self._base.pre_vars()
    def post_vars(self):
        return self._base.post_vars()
    def vars(self):
        return self._base.vars()
    def all(self):
        return self._base.all()
    def add_var(self, sort):
        return self._base.add_var(sort)
    def add_input(self, sort):
        return self._base.add_input(sort)

    def add_edge(self, src, dst, tr):
        self.nodes.add(src)
        self.nodes.add(dst)
        self.edges[(src, dst)] = tr

    def set_entry_node(self, n):
        self.nodes.add(n)
        self.entry = n
    def set_exit_node(self, n):
        self.nodes.add(n)
        self.exit = n

    def is_entry_node(self, n):
        return n == self.entry
    def is_exit_node(self, n):
        return n == self.exit

    def to_dot(self):
        import graphviz
        g = graphviz.Digraph()

        for n in self.nodes:
            g.node(str(n), str(n))

        for (k, v) in self.edges.items():
            src, dst = k
            g.edge(str(src), str(dst), label=str(v))

        return g

def cfa_vc_gen(A):
    '''Verification Condition (VC) for a Control Flow Automaton'''
    all_vars = A.all()
    sig = A.sig() + [z3.BoolSort()]

    Invs = dict()
    for n in A.nodes:
        inv = z3.Function(str(n), *sig)
        Invs[n] = inv

    Entry = Invs[A.entry]
    Exit = Invs[A.exit]

    vc = list()
    vc.append(z3.ForAll(all_vars, Entry(*A.pre_vars())))

    for (k, v) in A.edges.items():
        src, dst = k
        srcP, dstP = Invs[src], Invs[dst]

        head = dstP(*A.post_vars())
        sPred = srcP(*A.pre_vars())
        vc.append(z3.ForAll(all_vars, z3.Implies(z3.And(sPred, v), head)))
    vc.append(z3.ForAll(all_vars, z3.Implies(Exit(*A.pre_vars()), z3.BoolVal(False))))
    return vc, {n : Invs[n](A.pre_vars()) for n in A.nodes} 

def vc_gen_pa(T, preds):
    '''Verification Condition for Predicate Abstraction'''

    post_preds = [T.to_post(p) for p in preds]

    # create predicate Inv
    sig = [z3.BoolSort()] * (len(preds) + 1)
    Inv = z3.Function('InvPredAbs', *sig)

    all_vars = T.all()

    InvPre = Inv(*preds)
    InvPost = Inv(*post_preds)
    vc_init = z3.ForAll(all_vars, z3.Implies(T.Init, InvPre))
    vc_ind = z3.ForAll(all_vars, z3.Implies(z3.And(InvPre, T.Tr), InvPost))
    vc_bad = z3.ForAll(all_vars, z3.Implies(z3.And(InvPre, T.Bad), z3.BoolVal(False)))

    return [vc_init, vc_ind, vc_bad], InvPre

def vc_gen_ta(T, terms):
    '''Verification Condition for Term Abstraction'''

    post_terms = [T.to_post(p) for p in terms]

    # create term Inv
    sig = [t.sort() for t in terms] + [z3.BoolSort()]
    Inv = z3.Function('InvTermAbs', *sig)
    all_vars = T.all()

    InvPre = Inv(*terms)
    InvPost = Inv(*post_terms)

    vc_init = z3.ForAll(all_vars, z3.Implies(T.Init, InvPre))
    vc_ind = z3.ForAll(all_vars, z3.Implies(z3.And(InvPre, T.Tr), InvPost))
    vc_bad = z3.ForAll(all_vars, z3.Implies(z3.And(InvPre, T.Bad), z3.BoolVal(False)))

    return [vc_init, vc_ind, vc_bad], InvPre

def free_arith_vars(fml):
    '''Returns the set of all integer uninterpreted constants in a given formula'''
    seen = set([])
    vars = set([])

    int_sort = z3.IntSort()
    def fv(seen, vars, f):
        if f in seen:
            return
        seen |= { f }
        if f.sort().eq(int_sort) and f.decl().kind() == z3.Z3_OP_UNINTERPRETED:
            vars |= { f }
        for ch in f.children():
            fv(seen, vars, ch)
    fv(seen, vars, fml)
    return vars

def interpolate(A, B, verbosity=0):
    '''Computes a Craig interpolant between A and B'''
    As = free_arith_vars(A)
    Bs = free_arith_vars(B)

    shared = [s for s in As & Bs ]

    I = z3.Function('Itp', [s.sort() for s in shared] + [z3.BoolSort()])
    left = z3.ForAll([a for a in As], z3.Implies(A, I(shared)))
    right = z3.ForAll([b for b in Bs], z3.Implies(I(shared), z3.Not(B)))

    if verbosity > 0:
        print(left)
        print(right)

    s = z3.SolverFor("HORN")
    s.set("fp.xform.inline_eager", False)
    s.set("fp.xform.inline_linear", False)
    s.add(left)
    s.add(right)

    is_sat = s.check()
    if is_sat == z3.sat:
        mdl = s.model()
        if verbosity > 0:
            print(I(shared))
            print(mdl.decls())
            print(mdl)
            print(mdl.sexpr())
        interpolant = mdl.eval(I(shared))
        return interpolant
    else:
        return None

def mk_ts0(safe=True):
    T = Ts('Ts0')
    x, x_out = T.add_var(z3.IntSort(), name='x')
    T.Init = x <= 0
    T.Tr = z3.And(x < 5, x_out == x + 1)
    if safe:
        T.Bad = x >= 10
    else:
        T.Bad = x >= 4
    return T

def mk_ts1(safe=True):
    T = Ts('Ts1')
    a, a_out = T.add_var(z3.IntSort(), name='a')
    b, b_out = T.add_var(z3.IntSort(), name='b')
    c, c_out = T.add_var(z3.IntSort(), name='c')
    T.Init = z3.And(a == 0, 0 < c, c < 5, b == 3 * c)
    T.Tr = z3.And(a < 200, a_out == a + 1, b_out == b + 1)
    if safe:
        T.Bad = z3.Not(z3.And(3 <= b, b <= 200 + 12))
    else:
        T.Bad = z3.Not(z3.And(3 <= b, b <= 200 + 2))
    return T

def mk_ts2():
    T = Ts('Ts2')
    a, a_out = T.add_var(z3.IntSort(), name='a')
    b, b_out = T.add_var(z3.IntSort(), name='b')
    c, c_out = T.add_var(z3.IntSort(), name='c')
    d, d_out = T.add_var(z3.IntSort(), name='d')
    T.Init = z3.And(a == 0, b == 0, c == 0, d == 0)
    T.Tr = z3.And(a_out == a + 1,
                  b_out == b + a + 1,
                  c_out == c + b + a + 1,
                  d_out == d + c + b + a + 1)
    T.Bad = z3.Not(d >= 0)
    return T

def solve_horn(chc, pp=False, max_unfold=10, verbosity=0):
    z3.set_param(verbose=verbosity)

    s = z3.SolverFor('HORN')
    if not pp:
        s.set('xform.inline_eager', False)
        s.set('xform.inline_linear', False)
        s.set('xform.slice', False)
        s.set('engine', 'spacer')

    if max_unfold > 0:
        s.set('spacer.max_level', max_unfold)


    s.add(chc)
    if verbosity > 0:
        print(s.sexpr())
    res = s.check()
    print('result is', res)
    answer = None
    if res == z3.sat:
        answer = s.model()
    elif res == z3.unsat:
        answer = s.proof()
    return res, answer

def chc_to_str(chc):
    if z3.in_html_mode():
        return chc_to_html(chc)
    else:
        return chc_to_txt(chc)

def chc_to_html(chc):
    import io
    out = io.StringIO()

    for cls in chc:
        print(cls, '<br/>', file=out)

    return HtmlStr(out.getvalue())

def chc_to_txt(chc):
    import io
    out = io.StringIO()
    for cls in chc:
        print(cls, file=out)
    return out.getvalue()

class SpacerProof(object):
    def __init__(self, pf_ast):
        self._ast = pf_ast

    def _get_fact(self, ast):
        return ast.children()[-1]

    def _to_dot_rec(self, ast, graph, visited):
        if ast in visited:
            return

        visited.add(ast)

        dst = str(self._get_fact(ast).get_id())
        kids = ast.children()
        for k in kids[1:-1]:
            k_fact = self._get_fact(k)
            if k_fact not in visited:
                graph.node(str(k_fact.get_id()), str(k_fact))
                visited.add(k_fact)
                self._to_dot_rec(k, graph, visited)
            graph.edge(str(k_fact.get_id()), dst)

    def to_dot(self):
        import graphviz
        g = graphviz.Digraph()

        visited = set()

        fact = self._get_fact(self._ast)
        id = fact.get_id()
        g.node(str(id), str(fact))
        visited.add(id)
        self._to_dot_rec(self._ast, g, visited)
        return g

    def _repr_svg_(self):
        return self.to_dot()._repr_svg_()

    def __str__(self):
        return str(self.to_dot())
    def raw(self):
        return self._ast

def test_itp():
    a, b, x, y = z3.Ints('a b x y')
    itp = interpolate(z3.And(a < x, x < b), z3.And(b < a))
    print("Interpolant:", itp)

def test_vc(safe=True):
    T = mk_ts0(safe)
    vc, inv = vc_gen(T)
    print(chc_to_str(vc))
    if safe:
        res, model = solve_horn(vc)
        print(res)
        print(model.eval(inv))
    else:
        res, pf = solve_horn(vc)
        print(res)
        spf = SpacerProof(pf)
        print(spf)

def test_vc_bwd(safe=True):
    T = mk_ts0(safe)
    vc, inv = vc_gen_bwd(T)
    print(chc_to_str(vc))
    if safe:
        res, model = solve_horn(vc)
        print(res)
        print(model.eval(inv))
    else:
        res, pf = solve_horn(vc)
        print(res)
        spf = SpacerProof(pf)
        print(spf)

def mk_cfa0(safe=True):
    A = CFA('prog')
    x, x_out = A.add_var(z3.IntSort())

    A.add_edge('L0', 'L1', x_out == 0)
    A.add_edge('L1', 'L1', z3.And(x <= 5, x_out == x + 1))
    if safe:
        A.add_edge('L1', 'L2', x >= 10)
    else:
        A.add_edge('L1', 'L2', x >= 4)

    A.set_entry_node('L0')
    A.set_exit_node('L2')
    return A

def test_vc_cfa(safe=True):
    A = mk_cfa0(safe)

    vc, inv_map = cfa_vc_gen(A)
    print(chc_to_str(vc))
    if safe:
        res, model = solve_horn(vc)
        print(res)
        for k, v in inv_map.items():
            print('Inv at', k, 'is', model.eval(v))
    else:
        res, pf = solve_horn(vc)
        print(res)
        spf = SpacerProof(pf)
        print(spf)

def test_vc_pa():
    T = mk_ts0()
    x = T.get_pre_var('x')
    vc, inv = vc_gen_pa(T, [x <= 5, x <= 6, x <= 10])
    print(chc_to_str(vc))
    res, model = solve_horn(vc)
    print(res)
    print(model.eval(inv))

def test_vc_ta():
    T = mk_ts0()
    x = T.get_pre_var('x')
    vc, inv = vc_gen_ta(T, [x <= 5, x <= 6, x <= 10])
    print(chc_to_str(vc))
    res, model = solve_horn(vc)
    print(res)
    print(model.eval(inv))


def test_vc_ta2(safe=True):
    Ts = mk_ts1(safe)

    chc, inv = vc_gen(Ts)
    res, answer = solve_horn(chc)
    print(res)

    a, b, c = Ts.get_pre_vars('a b c')
    vc, inv = vc_gen_ta(Ts, [b-a, a])
    print(chc_to_str(vc))
    if safe:
        res, mdl= solve_horn(vc, max_unfold=400, verbosity=0)
        print(res)
        print(mdl.eval(inv))
    else:
        res, pf = solve_horn(vc, max_unfold=400)
        print(res)
        spf = SpacerProof(pf)
        print(spf)

def test_vc_pa3():
    Ts = mk_ts2()

    vc, inv = vc_gen(Ts)
    print(chc_to_str(vc))
    res, answer = solve_horn(vc, verbosity=0)
    print(res)

    a, b, c, d = Ts.get_pre_vars('a b c d')
    vc, inv = vc_gen_pa(Ts, [a >= 0, b >= 0, c >= 0, d >= 0])
    print(chc_to_str(vc))
    res, mdl = solve_horn(vc)
    print(res)
    print(mdl.eval(inv))


def main():
    # proof mode must be enabled before any expressions are created
    z3.set_param(proof=True)
    z3.set_param(model=True)

    test_itp()

    test_vc(safe=True)
    test_vc(safe=False)

    test_vc_bwd(safe=True)
    test_vc_bwd(safe=False)

    test_vc_cfa(safe=True)
    test_vc_cfa(safe=False)

    test_vc_pa()

    test_vc_ta()

    test_vc_ta2(safe=True)
    test_vc_ta2(safe=False)


    test_vc_pa3()


if __name__ == '__main__':
    sys.exit(main())

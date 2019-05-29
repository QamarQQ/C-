from itertools import chain  # Py 2.7 does not support func(*args1, *args2)
import sympy as sym
from scipy.integrate import odeint

class ODEsys(object):

    default_integrator = 'odeint'

    def __init__(self, f, y, t=None, params=(), tex_names=None, lambdify=None):
        assert len(f) == len(y), 'f is dy/dt'
        self.f = tuple(f)
        self.y = tuple(y)
        self.t = t
        self.p = tuple(params)
        self.tex_names = tex_names
        self.j = sym.Matrix(self.ny, 1, f).jacobian(y)
        self.lambdify = lambdify or sym.lambdify
        self.setup()

    @property
    def ny(self):
        return len(self.y)

    def setup(self):
        self.lambdified_f = self.lambdify(self.y + self.p, self.f)
        self.lambdified_j = self.lambdify(self.y + self.p, self.j)

    def f_eval(self, y, t, *params):
        return self.lambdified_f(*chain(y, params))

    def j_eval(self, y, t, *params):
        return self.lambdified_j(*chain(y, params))

    def integrate(self, *args, **kwargs):
        integrator = kwargs.pop('integrator', self.default_integrator)
        return getattr(self, 'integrate_%s' % integrator)(*args, **kwargs)

    def integrate_odeint(self, tout, y0, params=(), rtol=1e-8, atol=1e-8, **kwargs):
        return odeint(self.f_eval, y0, tout, args=tuple(params), full_output=True,
                      Dfun=self.j_eval, rtol=rtol, atol=atol, **kwargs)

    def print_info(self, info):
        if info is None:
            return
        nrhs = info.get('num_rhs')
        if not nrhs:
            nrhs = info['nfe'][-1]
        njac = info.get('num_dls_jac_evals')
        if not njac:
            njac = info['nje'][-1]
        print("The rhs was evaluated %d times and the jacobian %d times" % (nrhs, njac))

    def plot_result(self, tout, yout, info=None, ax=None):
        ax = ax or plt.subplot(1, 1, 1)
        for i, label in enumerate(self.tex_names):
            ax.plot(tout, yout[:, i], label='$%s$' % label)
        ax.set_ylabel('$\mathrm{concentration\ /\ mol \cdot dm^{-3}}$')
        ax.set_xlabel('$\mathrm{time\ /\ s}$')
        ax.legend(loc='best')
        self.print_info(info)

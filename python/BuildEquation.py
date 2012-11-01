import scipy
import sys
import string

def lagrange(points):
   """ Lagrange Interpolation through a set of points """
   tmp = scipy.poly1d([0])
   result=scipy.poly1d([0])
   for i in points.keys():
      numerator=scipy.poly1d([1])
      denom = 1.0
      for j in points.keys():
         if (i != j):
            tmp = scipy.poly1d([1,-j])
            numerator = numerator * tmp
            denom = denom * (i - j)
      tmp = (numerator/denom) * points.get(i)
      result = result + tmp
   return result

sys.stdin.readline()
sys.stdin.readline()
sys.stdin.readline()

ins = {}

for l in sys.stdin:
   x, y = map(float, l.split())
   ins[x] = -y

print ins

pol = lagrange(ins)
print pol

deg = len(pol.c) -1

t = ""
for coef in pol.c:
   s = "%.8f" % (coef)
   if deg > 0:
      s += "*x"

   if deg > 1:
      s += "^" + str(deg)

   if coef > 0:
      s = "+" + s

   deg -= 1
   t += s

t += " + 0.1*sin(20*x)"

print t


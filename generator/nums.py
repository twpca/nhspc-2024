"""nums"""
import random

def out(subtask, variant, k, testdata):
  """out"""
  fn = '%d_%s_%d.in' % (subtask, variant, k)
  random.shuffle(testdata)
  for i in range(0, len(testdata)):
    testdata[i] = testdata[i].lstrip('0')

  with open(fn, 'w') as f:
    print(len(testdata), file=f)
    print(' '.join(testdata), file=f)

def random_string(l, no_leading_zero=False):
  """random_string"""
  res = ''.join(random.choices('0123456789', k=l))
  while res[0] == '0' and no_leading_zero:
    res = ''.join(random.choices('0123456789', k=l))
  return res

def replace_string(s, k, no_leading_zero=False):
  """replace_string"""
  s = list(s)
  for _ in range(0, k):
    p1, p2 = random.choices(range(0, len(s)), k=2)
    while no_leading_zero and ((p1 == 0 and s[p2] == '0') or (p2 == 0 and s[p1] == '0')):
      p1, p2 = random.choices(range(0, len(s)), k=2)
    s[p1], s[p2] = s[p2], s[p1]
  return ''.join(s)

def mod_string(s, k, no_leading_zero=False):
  """mod_string: mod k places"""
  s = list(s)
  for _ in range(0, k):
    p = random.choice(range(0, len(s)))
    while no_leading_zero and p == 0:
      p = random.choice(range(0, len(s)))
    s[p] = str(random.choice(range(0, 10)))
  return ''.join(s)

def gen(n, m, pnew=0.1, pmod=0.3, no_leading_zero=False):
  s = set()
  res = []
  res.append(random_string(m, no_leading_zero=no_leading_zero))
  s.add(res[0])

  for _ in range(0, n-1):
    ddice = random.uniform(0, 1)
    if ddice <= pnew:
      nnum = random_string(m, no_leading_zero=no_leading_zero)
      while nnum in s:
        nnum = random_string(m, no_leading_zero=no_leading_zero)
      res.append(nnum)
      s.add(nnum)
    elif ddice <= pnew + pmod:
      p = random.randint(0, len(res)-1)
      places = random.randint(1, 10)
      nnum = mod_string(res[p], places, no_leading_zero=no_leading_zero)
      while nnum in s:
        places = random.randint(1, 10)
        nnum = mod_string(res[p], places, no_leading_zero=no_leading_zero)
      res.append(nnum)
      s.add(nnum)
    else:
      p = random.randint(0, len(res)-1)
      places = random.randint(1, 5)
      nnum = replace_string(res[p], places, no_leading_zero=no_leading_zero)
      while nnum in s:
        places = random.randint(1, 5)
        nnum = replace_string(res[p], places, no_leading_zero=no_leading_zero)
      res.append(nnum)
      s.add(nnum)

  return res

def subtask1():
  n = 20
  m = 5
  for k in range(1, 11):
    testdata = gen(n, m, no_leading_zero=True)
    out(1, 'rand', k, testdata)

def subtask2():
  for k in range(1, 6):
    n = random.randint(50, 100)
    m = random.randint(250, 500)
    testdata = gen(n, m)
    out(2, 'rand', k, testdata)

  for k in range(1, 6):
    n = random.randint(95, 100)
    m = random.randint(250, 500)
    testdata = gen(n, m)
    out(2, 'rand_maxn', k, testdata)

  for k in range(1, 6):
    n = random.randint(95, 100)
    m = random.randint(495, 500)
    testdata = gen(n, m)
    out(2, 'rand_maxmn', k, testdata)

def subtask3():
  for k in range(1, 6):
    n = random.randint(50, 100)
    m = random.randint(2500, 5000)
    testdata = gen(n, m)
    out(3, 'rand', k, testdata)

  for k in range(1, 6):
    n = random.randint(95, 100)
    m = random.randint(2500, 5000)
    testdata = gen(n, m)
    out(3, 'rand_maxn', k, testdata)

  for k in range(1, 6):
    n = random.randint(95, 100)
    m = random.randint(4950, 5000)
    testdata = gen(n, m)
    out(3, 'rand_maxmn', k, testdata)

def main():
  """main"""
  random.seed(114514)
  subtask1()
  subtask2()
  subtask3()

if __name__ == '__main__':
  main()

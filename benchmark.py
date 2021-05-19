#!/usr/bin/env python
# coding: utf-8

# In[1]:


import numpy as np
from numba import njit, prange


# In[28]:


def f_numpy(a, b, c):
    c[0] = a[0]**2 + b[0]**2 + a[0]*b[0]
    c[1:] = a[1:]**2+b[:-1]**2 + a[1:]*b[1:] + a[1:] + b[1:]
    


# In[30]:


@njit(parallel=True)
def f_numba_p(a,b,c):
    for i in prange(c.shape[0]):
        if i == 0:
            c[i] = a[i]**2+b[i]**2 + a[i]*b[i] 
            continue
        c[i] = a[i]**2+b[i-1]**2 + a[i]*b[i] + a[i] + b[i]
    


# In[31]:


@njit
def f_numba(a,b,c):
    for i in range(c.shape[0]):
        if i == 0:
            c[i] = a[i]**2+b[i]**2 + a[i]*b[i] 
            continue
        c[i] = a[i]**2+b[i-1]**2 + a[i]*b[i] + a[i] + b[i]
    


# In[32]:


N = 100000
# a = np.random.rand(N)
# b = np.random.rand(N)
a = np.arange(N)+0.2174
b = np.arange(N)+0.8903
c = np.zeros(N)


# In[36]:

print("numpy:")
get_ipython().run_cell_magic('timeit', '', 'f_numpy(a,b,c)')


# In[37]:


print("numba:")
get_ipython().run_cell_magic('timeit', '', 'f_numba(a,b,c)')


# In[38]:


print("numba parallel")
get_ipython().run_cell_magic('timeit', '', 'f_numba_p(a,b,c)')


# In[ ]:





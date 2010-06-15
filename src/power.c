#include "power.h"

int power_linear_roots(float A, float B, float** roots)
{
  if(A == 0)
  {
    // function is constant and we treat f(x) == 0 as no roots
    return 0;
  }
  else
  {
    float root = -B / A;
    *roots = malloc(sizeof(float));
    (*roots)[0] = root;
    return 1;
  }
}

int power_quad_roots(float A, float B, float C, float** roots)
{
  if(A == 0)
  {
    return power_linear_roots(B, C, roots);
  }
  else
  {
    float delta = B*B - 4*A*C;
  
    if(delta < 0)
    {
      *roots = 0;
      return 0;
    }
    else
    {
      // quadratic formula and scaling from [0,1] to [a,b]
      float lroot = (-B - sqrtf(delta)) / (2*A);
      float rroot = (-B + sqrtf(delta)) / (2*A);
      
      if(lroot > rroot)
      {
	swap(&lroot, &rroot);
      }
      
      assert(lroot <= rroot);
      
      if(lroot == rroot)
      {
	*roots = malloc(sizeof(float));
	(*roots)[0] = lroot;
	return 1;
      }
      else
      {
	*roots = malloc(2 * sizeof(float));
	(*roots)[0] = lroot;
	(*roots)[1] = rroot;
	return 2;
      }
    }
  }
}

int power_cubic_roots(float A, float B, float C, float D, float** roots)
{
  if(A == 0)
  {
    return power_quad_roots(B, C, D, roots);
  }
  else
  {
    *roots = malloc(sizeof(float) * 3);
    
    float w = B / (3 * A);
    float p = (C / (3 * A) - w*w)*(C / (3 * A) - w*w)*(C / (3 * A) - w*w);
    float q = -0.5 * (2 * w*w*w - (C * w - D) / A);
    float delta = q*q + p;
    
    if(delta < 0.0)
    {
      float h = q / sqrt(-p);
      float phi = acos(max(-1.0, min(1.0, h)));
      p = 2 * pow(-p, 1.0 / 6.0);

      int inserter = 0;
      for(; inserter < 3; inserter++)
	(*roots)[inserter] = p * cos((phi + 2 * inserter * PI) / 3.0) - w;
      
      // todo: sort roots
      // todo: remove out of range
      
      return 3;
    }
    else
    {
      delta = sqrt(delta);
      *roots = malloc(sizeof(float));
      (*roots)[0] = (q + delta)*(q + delta)*(q + delta)*(q + delta) + (q - delta)*(q - delta)*(q - delta)*(q - delta) - w;
      return 1;
    }
  }
}


#include <cstdlib>
using namespace std;

void setSeed(
    const int seedVal
    )
{
  srand(seedVal);
}

int getUniform(
     const int min,
     const int max
     )
{
  int uniRand;
  uniRand = rand() % ((max + 1) - min) + min;
  return (uniRand);
}

int getNormal(
     const double mean,
     const double stdDev
     )
{
  const int NUM_UNIFORM = 12;
  const int MAX = 1000;
  const double ORIGINAL_MEAN = NUM_UNIFORM * 0.5;
  double sum;
  int i;
  double standardNormal;
  double newNormal;
  int uni;

  sum = 0;
  for (i = 0; i < NUM_UNIFORM; i++)
  {
    uni = rand() % (MAX + 1);
    sum += uni;
  }
  sum = sum / MAX;
  standardNormal = sum - ORIGINAL_MEAN;
  newNormal = mean + stdDev * standardNormal;
  if (newNormal < 0)
  {
    newNormal *= - 1;
  }
  return ((int)newNormal);
}

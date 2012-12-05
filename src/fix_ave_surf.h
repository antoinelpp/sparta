/* ----------------------------------------------------------------------
   SPARTA - Stochastic PArallel Rarefied-gas Time-accurate Analyzer
   http://sparta.sandia.gov
   Steve Plimpton, sjplimp@sandia.gov, Michael Gallis, magalli@sandia.gov
   Sandia National Laboratories

   Copyright (2012) Sandia Corporation.  Under the terms of Contract
   DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
   certain rights in this software.  This software is distributed under 
   the GNU General Public License.

   See the README file in the top-level SPARTA directory.
------------------------------------------------------------------------- */

#ifdef FIX_CLASS

FixStyle(ave/surf,FixAveSurf)

#else

#ifndef LMP_FIX_AVE_SURF_H
#define LMP_FIX_AVE_SURF_H

#include "fix.h"

namespace SPARTA_NS {

class FixAveSurf : public Fix {
 public:
  FixAveSurf(class SPARTA *, int, char **);
  ~FixAveSurf();
  int setmask();
  void init();
  void setup();
  void end_of_step();
  double memory_usage();

 private:
  int nvalues,maxvalues;
  int nevery,nrepeat,irepeat,nsample,ave;
  bigint nvalid;
  int *which,*argindex,*value2index;
  char **ids;

  int nslocal;               // # of surfs I own
  double *accvec;            // accumulation vector
  double **accarray;         // accumulation array

  int nsurf;               // # of global surfs, lines or triangles
  int nlocal;              // # of local surfs
  int maxlocal;            // # of local surfs currently allocated
  int *glob2loc;           // glob2loc[I] = local index of Ith global surf
  int *loc2glob;           // loc2glob[I] = global index of Ith local surf

  double *vec_local;
  double **array_local;

  void options(int, char **);
  void grow();
  void grow_local();
  bigint nextvalid();
};

}

#endif
#endif
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

#ifdef DUMP_CLASS

DumpStyle(surf,DumpSurf)

#else

#ifndef SPARTA_DUMP_SURF_H
#define SPARTA_DUMP_SURF_H

#include "dump.h"

namespace SPARTA_NS {

class DumpSurf : public Dump {
 public:
  DumpSurf(class SPARTA *, int, char **);
  ~DumpSurf();

 protected:
  int nevery;                // dump frequency to check Fix against

  int *vtype;                // type of each vector (INT, DOUBLE)
  char **vformat;            // format string for each vector element

  char *columns;             // column labels

  int nfield;                // # of keywords listed by user
  int ioptional;             // index of start of optional args

  int *field2arg;            // which arg for each field, since args may expand

  int *field2index;          // which compute,fix,variable calcs this field
  int *argindex;             // index into compute,fix scalar_atom,vector_atom
                             // 0 for scalar_atom, 1-N for vector_atom values
  int ncompute;              // # of Compute objects used by dump
  char **id_compute;         // their IDs
  class Compute **compute;   // list of ptrs to the Compute objects

  int nfix;                  // # of Fix objects used by dump
  char **id_fix;             // their IDs
  class Fix **fix;           // list of ptrs to the Fix objects

  int nvariable;             // # of Variables used by dump
  char **id_variable;        // their names
  int *variable;             // list of indices for the Variables
  double **vbuf;             // local storage for variable evaluation

  int dimension;
  int nslocal;               // # of surf elements on this proc

  // private methods

  virtual void init_style();
  virtual void write_header(bigint);
  int count();
  void pack();
  virtual void write_data(int, double *);

  int parse_fields(int, char **);
  int add_compute(char *);
  int add_fix(char *);
  int add_variable(char *);
  void allocate_values(int);

  typedef void (DumpSurf::*FnPtrHeader)(bigint);
  FnPtrHeader header_choice;           // ptr to write header functions
  void header_binary(bigint);
  void header_item(bigint);

  typedef void (DumpSurf::*FnPtrData)(int, double *);
  FnPtrData write_choice;              // ptr to write data functions
  void write_binary(int, double *);
  void write_text(int, double *);

  // customize by adding a method prototype

  typedef void (DumpSurf::*FnPtrPack)(int);
  FnPtrPack *pack_choice;              // ptrs to pack functions

  void pack_compute(int);
  void pack_fix(int);
  void pack_variable(int);

  void pack_id(int);

  void pack_v1x(int);
  void pack_v1y(int);
  void pack_v1z(int);
  void pack_v2x(int);
  void pack_v2y(int);
  void pack_v2z(int);
  void pack_v3x(int);
  void pack_v3y(int);
  void pack_v3z(int);
};

}

#endif
#endif
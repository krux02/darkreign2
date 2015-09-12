/*
 *  MRMUpdate.h
 *
 *              INTEL CORPORATION PROPRIETARY INFORMATION
 *  This software is supplied under the terms of a license agreement or
 *  nondisclosure agreement with Intel Corporation and may not be copied
 *  or disclosed except in accordance with the terms of that agreement.
 *
 *      Copyright (c) 1998 Intel Corporation. All Rights Reserved.
 *
 *
 *  PURPOSE:
 *
 * This file defines the sample MRMUpdate records generated by MRMGen.dll.
 * You should consider these structures as a container type like linked 
 * lists.  We designed them for ease of use rather than efficiency.  Once
 * MRMGen has deposited data into the MRM Update records, their data can
 * be converted to optimized update records by the developer.
 */

/*
#ifndef UPDATE_DOT_H
#define UPDATE_DOT_H


#define MRM_BETA_VERSION "MRM 0.7                        "
#define MRM_VERSION "MRM 1.0                        "
#define MRM_VERSION_LENGTH 32


#include "IMESH.h"

extern "C"
{


#ifndef TRUE
#define FALSE 0
#define TRUE  1
typedef unsigned int BOOL;
#endif

//  FaceUpdate encapsulates a changed attribute within a face of
// an MRM model.  The following list of token identifiers indicate which 
// attributes  may be changed:

typedef enum 
{ 
	BadToken,
	VertexA, VertexB, VertexC, 
	NormalA, NormalB, NormalC, 
	TexCoord1A, TexCoord1B, TexCoord1C,
	TexCoord2A, TexCoord2B, TexCoord2C
} AttribToken;

typedef enum {Decreasing, Increasing} Direction;

typedef struct FaceUpdateTag
{
	unsigned long   faceIndex;		// Index of the IFACE to be changed
	AttribToken     attribToken;	// One of MRM_UPDATE_* tokens (defined above)
	unsigned long   value[2];		// [Decreasing]: Attribute value for resolution decrease.
									// [Increasing]: Attribute value for resolution increase.
} FaceUpdate;


typedef struct VertexUpdateTag
{
	unsigned long   vertexIndex;
	unsigned long   parentVertexIndex;
	unsigned short  numNewFaces;
	unsigned short	numNewNormals;
	unsigned short  numNewTexCoords;
	unsigned short  numFaceUpdates;	// Includes updates for new faces and old faces
	FaceUpdate      *faceUpdates;
} VertexUpdate;


typedef struct MRMUpdatesTag
{
	unsigned long   maxNumVertices;
	unsigned long   maxNumFaces;
	unsigned long   maxNumNormals;
	unsigned long   maxNumTexCoords;
	VertexUpdate    *vertexUpdates;
} MRMUpdates;


BOOL MRMRead            (IMESH **imesh, MRMUpdates **mrmUpdates, char *fileName);
BOOL MRMWrite           (IMESH *imesh, MRMUpdates *mrmUpdates, char *fileName);
void MRMIncrVertices    (MRMUpdates *mrmUpdates, IMESH *imesh, int r);
void MRMDecrVertices    (MRMUpdates *mrmUpdates, IMESH *imesh, int r);
void MRMSetNumVertices  (MRMUpdates *mrmUpdates, IMESH *imesh, int r);
BOOL MRMFree            (MRMUpdates *mrmUpdates);

} // extern "C"

#endif
*/

#ifndef UPDATE_DOT_H
#define UPDATE_DOT_H

/////////////////////////////////////////////////////////
/*-----------------------------------------------------*/
// VERSION DEFINES
#define MRM_BETA_VERSION		"MRM 0.7                        "
#define MRM_VERSION				"MRM 1.0                        "
#define MRM_VERSION_LENGTH		32

/*-----------------------------------------------------*/
/////////////////////////////////////////////////////////

#include "IMESH.h"

extern "C"
{


#ifndef TRUE
#define FALSE 0
#define TRUE  1
typedef unsigned int BOOL;
#endif


/////////////////////////////////////////////////////////
/*-----------------------------------------------------*/
// ENUMS

//  FaceUpdate encapsulates a changed attribute within a face of
// an MRM model.  The following list of token identifiers indicate which 
// attributes  may be changed:

typedef enum 
{ 
	BadToken,
	VertexA, VertexB, VertexC, 
	NormalA, NormalB, NormalC, 
	TexCoord1A, TexCoord1B, TexCoord1C,
	TexCoord2A, TexCoord2B, TexCoord2C,
	VtxA, VtxB, VtxC, 
} AttribToken;

typedef enum {Decreasing, Increasing} Direction;

/*-----------------------------------------------------*/
/////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////
/*-----------------------------------------------------*/
// STRUCTS
typedef struct FaceUpdateTag
{
	unsigned long   faceIndex;		// Index of the IFACE to be changed
	AttribToken     attribToken;	// One of MRM_UPDATE_* tokens (defined above)
	unsigned long   value[2];		// [Decreasing]: Attribute value for resolution decrease.
									// [Increasing]: Attribute value for resolution increase.
} FaceUpdate;


typedef struct VertexUpdateTag
{
	unsigned long   vertexIndex;
	unsigned long   parentVertexIndex;
	unsigned short  numNewFaces;
	unsigned short	numNewNormals;
	unsigned short  numNewTexCoords;
	unsigned short  numFaceUpdates;	// Includes updates for new faces and old faces
	FaceUpdate      *faceUpdates;
} VertexUpdate;


typedef struct MRMUpdatesTag
{
	unsigned long   maxNumVertices;
	unsigned long   maxNumFaces;
	unsigned long   maxNumNormals;
	unsigned long   maxNumTexCoords;

  VertexUpdate    *vertexUpdates;

  MRMUpdatesTag()
  {
    vertexUpdates = NULL;
  }
  ~MRMUpdatesTag()
  {
    Free();
  }

  void Alloc( unsigned long totalFaceUpdates);
  void Free();

} MRMUpdates;
/*-----------------------------------------------------*/
/////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////
/*-----------------------------------------------------*/
// PROTOTYPES
unsigned int getSize	(MRMUpdates *upd);
BOOL MRMRead            (IMESH **imesh, MRMUpdates **mrmUpdates, char *fileName);
BOOL MRMWrite           (IMESH *imesh, MRMUpdates *mrmUpdates, char *fileName);
void MRMIncrVertices    (MRMUpdates *mrmUpdates, IMESH *imesh, int r);
void MRMDecrVertices    (MRMUpdates *mrmUpdates, IMESH *imesh, int r);
void MRMSetNumVertices  (MRMUpdates *mrmUpdates, IMESH *imesh, int r);
BOOL MRMFree            (MRMUpdates *mrmUpdates);
/*-----------------------------------------------------*/
/////////////////////////////////////////////////////////


} // extern "C"

#endif

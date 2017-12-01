// This code contains NVIDIA Confidential Information and is disclosed to you
// under a form of NVIDIA software license agreement provided separately to you.
//
// Notice
// NVIDIA Corporation and its licensors retain all intellectual property and
// proprietary rights in and to this software and related documentation and
// any modifications thereto. Any use, reproduction, disclosure, or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA Corporation is strictly prohibited.
//
// ALL NVIDIA DESIGN SPECIFICATIONS, CODE ARE PROVIDED "AS IS.". NVIDIA MAKES
// NO WARRANTIES, EXPRESSED, IMPLIED, STATUTORY, OR OTHERWISE WITH RESPECT TO
// THE MATERIALS, AND EXPRESSLY DISCLAIMS ALL IMPLIED WARRANTIES OF NONINFRINGEMENT,
// MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE.
//
// Information and code furnished is believed to be accurate and reliable.
// However, NVIDIA Corporation assumes no responsibility for the consequences of use of such
// information or for any infringement of patents or other rights of third parties that may
// result from its use. No license is granted by implication or otherwise under any patent
// or patent rights of NVIDIA Corporation. Details are subject to change without notice.
// This code supersedes and replaces all information previously supplied.
// NVIDIA Corporation products are not authorized for use as critical
// components in life support devices or systems without express written approval of
// NVIDIA Corporation.
//
// Copyright (c) 2008-2017 NVIDIA Corporation. All rights reserved.

// This file was generated by NvParameterized/scripts/GenParameterized.pl


#include "EmitterGeomExplicitParams_0p1.h"
#include <string.h>
#include <stdlib.h>

using namespace NvParameterized;

namespace nvidia
{
namespace parameterized
{

using namespace EmitterGeomExplicitParams_0p1NS;

const char* const EmitterGeomExplicitParams_0p1Factory::vptr =
    NvParameterized::getVptr<EmitterGeomExplicitParams_0p1, EmitterGeomExplicitParams_0p1::ClassAlignment>();

const uint32_t NumParamDefs = 27;
static NvParameterized::DefinitionImpl* ParamDefTable; // now allocated in buildTree [NumParamDefs];


static const size_t ParamLookupChildrenTable[] =
{
	1, 2, 9, 17, 3, 7, 4, 5, 6, 8, 10, 15, 11, 12, 13, 14, 16, 18, 25, 19, 20, 21, 22,
	23, 24, 26,
};

#define TENUM(type) nvidia::##type
#define CHILDREN(index) &ParamLookupChildrenTable[index]
static const NvParameterized::ParamLookupNode ParamLookupTable[NumParamDefs] =
{
	{ TYPE_STRUCT, false, 0, CHILDREN(0), 4 },
	{ TYPE_F32, false, (size_t)(&((ParametersStruct*)0)->distance), NULL, 0 }, // distance
	{ TYPE_STRUCT, false, (size_t)(&((ParametersStruct*)0)->points), CHILDREN(4), 2 }, // points
	{ TYPE_ARRAY, true, (size_t)(&((ExplicitPoints_Type*)0)->positions), CHILDREN(6), 1 }, // points.positions
	{ TYPE_STRUCT, false, 1 * sizeof(PointParams_Type), CHILDREN(7), 2 }, // points.positions[]
	{ TYPE_VEC3, false, (size_t)(&((PointParams_Type*)0)->position), NULL, 0 }, // points.positions[].position
	{ TYPE_BOOL, false, (size_t)(&((PointParams_Type*)0)->doDetectOverlaps), NULL, 0 }, // points.positions[].doDetectOverlaps
	{ TYPE_ARRAY, true, (size_t)(&((ExplicitPoints_Type*)0)->velocities), CHILDREN(9), 1 }, // points.velocities
	{ TYPE_VEC3, false, 1 * sizeof(physx::PxVec3), NULL, 0 }, // points.velocities[]
	{ TYPE_STRUCT, false, (size_t)(&((ParametersStruct*)0)->spheres), CHILDREN(10), 2 }, // spheres
	{ TYPE_ARRAY, true, (size_t)(&((ExplicitSpheres_Type*)0)->positions), CHILDREN(12), 1 }, // spheres.positions
	{ TYPE_STRUCT, false, 1 * sizeof(SphereParams_Type), CHILDREN(13), 3 }, // spheres.positions[]
	{ TYPE_VEC3, false, (size_t)(&((SphereParams_Type*)0)->center), NULL, 0 }, // spheres.positions[].center
	{ TYPE_F32, false, (size_t)(&((SphereParams_Type*)0)->radius), NULL, 0 }, // spheres.positions[].radius
	{ TYPE_BOOL, false, (size_t)(&((SphereParams_Type*)0)->doDetectOverlaps), NULL, 0 }, // spheres.positions[].doDetectOverlaps
	{ TYPE_ARRAY, true, (size_t)(&((ExplicitSpheres_Type*)0)->velocities), CHILDREN(16), 1 }, // spheres.velocities
	{ TYPE_VEC3, false, 1 * sizeof(physx::PxVec3), NULL, 0 }, // spheres.velocities[]
	{ TYPE_STRUCT, false, (size_t)(&((ParametersStruct*)0)->ellipsoids), CHILDREN(17), 2 }, // ellipsoids
	{ TYPE_ARRAY, true, (size_t)(&((ExplicitEllipsoids_Type*)0)->positions), CHILDREN(19), 1 }, // ellipsoids.positions
	{ TYPE_STRUCT, false, 1 * sizeof(EllipsoidParams_Type), CHILDREN(20), 5 }, // ellipsoids.positions[]
	{ TYPE_VEC3, false, (size_t)(&((EllipsoidParams_Type*)0)->center), NULL, 0 }, // ellipsoids.positions[].center
	{ TYPE_F32, false, (size_t)(&((EllipsoidParams_Type*)0)->radius), NULL, 0 }, // ellipsoids.positions[].radius
	{ TYPE_VEC3, false, (size_t)(&((EllipsoidParams_Type*)0)->normal), NULL, 0 }, // ellipsoids.positions[].normal
	{ TYPE_F32, false, (size_t)(&((EllipsoidParams_Type*)0)->polarRadius), NULL, 0 }, // ellipsoids.positions[].polarRadius
	{ TYPE_BOOL, false, (size_t)(&((EllipsoidParams_Type*)0)->doDetectOverlaps), NULL, 0 }, // ellipsoids.positions[].doDetectOverlaps
	{ TYPE_ARRAY, true, (size_t)(&((ExplicitEllipsoids_Type*)0)->velocities), CHILDREN(25), 1 }, // ellipsoids.velocities
	{ TYPE_VEC3, false, 1 * sizeof(physx::PxVec3), NULL, 0 }, // ellipsoids.velocities[]
};


bool EmitterGeomExplicitParams_0p1::mBuiltFlag = false;
NvParameterized::MutexType EmitterGeomExplicitParams_0p1::mBuiltFlagMutex;

EmitterGeomExplicitParams_0p1::EmitterGeomExplicitParams_0p1(NvParameterized::Traits* traits, void* buf, int32_t* refCount) :
	NvParameters(traits, buf, refCount)
{
	//mParameterizedTraits->registerFactory(className(), &EmitterGeomExplicitParams_0p1FactoryInst);

	if (!buf) //Do not init data if it is inplace-deserialized
	{
		initDynamicArrays();
		initStrings();
		initReferences();
		initDefaults();
	}
}

EmitterGeomExplicitParams_0p1::~EmitterGeomExplicitParams_0p1()
{
	freeStrings();
	freeReferences();
	freeDynamicArrays();
}

void EmitterGeomExplicitParams_0p1::destroy()
{
	// We cache these fields here to avoid overwrite in destructor
	bool doDeallocateSelf = mDoDeallocateSelf;
	NvParameterized::Traits* traits = mParameterizedTraits;
	int32_t* refCount = mRefCount;
	void* buf = mBuffer;

	this->~EmitterGeomExplicitParams_0p1();

	NvParameters::destroy(this, traits, doDeallocateSelf, refCount, buf);
}

const NvParameterized::DefinitionImpl* EmitterGeomExplicitParams_0p1::getParameterDefinitionTree(void)
{
	if (!mBuiltFlag) // Double-checked lock
	{
		NvParameterized::MutexType::ScopedLock lock(mBuiltFlagMutex);
		if (!mBuiltFlag)
		{
			buildTree();
		}
	}

	return(&ParamDefTable[0]);
}

const NvParameterized::DefinitionImpl* EmitterGeomExplicitParams_0p1::getParameterDefinitionTree(void) const
{
	EmitterGeomExplicitParams_0p1* tmpParam = const_cast<EmitterGeomExplicitParams_0p1*>(this);

	if (!mBuiltFlag) // Double-checked lock
	{
		NvParameterized::MutexType::ScopedLock lock(mBuiltFlagMutex);
		if (!mBuiltFlag)
		{
			tmpParam->buildTree();
		}
	}

	return(&ParamDefTable[0]);
}

NvParameterized::ErrorType EmitterGeomExplicitParams_0p1::getParameterHandle(const char* long_name, Handle& handle) const
{
	ErrorType Ret = NvParameters::getParameterHandle(long_name, handle);
	if (Ret != ERROR_NONE)
	{
		return(Ret);
	}

	size_t offset;
	void* ptr;

	getVarPtr(handle, ptr, offset);

	if (ptr == NULL)
	{
		return(ERROR_INDEX_OUT_OF_RANGE);
	}

	return(ERROR_NONE);
}

NvParameterized::ErrorType EmitterGeomExplicitParams_0p1::getParameterHandle(const char* long_name, Handle& handle)
{
	ErrorType Ret = NvParameters::getParameterHandle(long_name, handle);
	if (Ret != ERROR_NONE)
	{
		return(Ret);
	}

	size_t offset;
	void* ptr;

	getVarPtr(handle, ptr, offset);

	if (ptr == NULL)
	{
		return(ERROR_INDEX_OUT_OF_RANGE);
	}

	return(ERROR_NONE);
}

void EmitterGeomExplicitParams_0p1::getVarPtr(const Handle& handle, void*& ptr, size_t& offset) const
{
	ptr = getVarPtrHelper(&ParamLookupTable[0], const_cast<EmitterGeomExplicitParams_0p1::ParametersStruct*>(&parameters()), handle, offset);
}


/* Dynamic Handle Indices */

void EmitterGeomExplicitParams_0p1::freeParameterDefinitionTable(NvParameterized::Traits* traits)
{
	if (!traits)
	{
		return;
	}

	if (!mBuiltFlag) // Double-checked lock
	{
		return;
	}

	NvParameterized::MutexType::ScopedLock lock(mBuiltFlagMutex);

	if (!mBuiltFlag)
	{
		return;
	}

	for (uint32_t i = 0; i < NumParamDefs; ++i)
	{
		ParamDefTable[i].~DefinitionImpl();
	}

	traits->free(ParamDefTable);

	mBuiltFlag = false;
}

#define PDEF_PTR(index) (&ParamDefTable[index])

void EmitterGeomExplicitParams_0p1::buildTree(void)
{

	uint32_t allocSize = sizeof(NvParameterized::DefinitionImpl) * NumParamDefs;
	ParamDefTable = (NvParameterized::DefinitionImpl*)(mParameterizedTraits->alloc(allocSize));
	memset(ParamDefTable, 0, allocSize);

	for (uint32_t i = 0; i < NumParamDefs; ++i)
	{
		NV_PARAM_PLACEMENT_NEW(ParamDefTable + i, NvParameterized::DefinitionImpl)(*mParameterizedTraits);
	}

	// Initialize DefinitionImpl node: nodeIndex=0, longName=""
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[0];
		ParamDef->init("", TYPE_STRUCT, "STRUCT", true);






	}

	// Initialize DefinitionImpl node: nodeIndex=1, longName="distance"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[1];
		ParamDef->init("distance", TYPE_F32, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("gameScale", "true", true);
		HintTable[1].init("min", double(0.0f), true);
		ParamDefTable[1].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#else

		static HintImpl HintTable[3];
		static Hint* HintPtrTable[3] = { &HintTable[0], &HintTable[1], &HintTable[2], };
		HintTable[0].init("gameScale", "true", true);
		HintTable[1].init("min", double(0.0f), true);
		HintTable[2].init("shortDescription", "Average distance between particles", true);
		ParamDefTable[1].setHints((const NvParameterized::Hint**)HintPtrTable, 3);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=2, longName="points"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[2];
		ParamDef->init("points", TYPE_STRUCT, "ExplicitPoints", true);






	}

	// Initialize DefinitionImpl node: nodeIndex=3, longName="points.positions"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[3];
		ParamDef->init("positions", TYPE_ARRAY, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("gameScale", "true", true);
		ParamDefTable[3].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("gameScale", "true", true);
		HintTable[1].init("shortDescription", "List of point positions", true);
		ParamDefTable[3].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */




		ParamDef->setArraySize(-1);
	}

	// Initialize DefinitionImpl node: nodeIndex=4, longName="points.positions[]"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[4];
		ParamDef->init("positions", TYPE_STRUCT, "PointParams", true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("gameScale", "true", true);
		ParamDefTable[4].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("gameScale", "true", true);
		HintTable[1].init("shortDescription", "List of point positions", true);
		ParamDefTable[4].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=5, longName="points.positions[].position"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[5];
		ParamDef->init("position", TYPE_VEC3, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("gameScale", "true", true);
		ParamDefTable[5].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("gameScale", "true", true);
		HintTable[1].init("shortDescription", "Initial position", true);
		ParamDefTable[5].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=6, longName="points.positions[].doDetectOverlaps"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[6];
		ParamDef->init("doDetectOverlaps", TYPE_BOOL, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("defaultValue", "false", true);
		ParamDefTable[6].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("defaultValue", "false", true);
		HintTable[1].init("shortDescription", "Avoid overlaps with other shapes?", true);
		ParamDefTable[6].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=7, longName="points.velocities"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[7];
		ParamDef->init("velocities", TYPE_ARRAY, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("gameScale", "true", true);
		ParamDefTable[7].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("gameScale", "true", true);
		HintTable[1].init("shortDescription", "List of initial velocities", true);
		ParamDefTable[7].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */




		ParamDef->setArraySize(-1);
	}

	// Initialize DefinitionImpl node: nodeIndex=8, longName="points.velocities[]"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[8];
		ParamDef->init("velocities", TYPE_VEC3, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("gameScale", "true", true);
		ParamDefTable[8].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("gameScale", "true", true);
		HintTable[1].init("shortDescription", "List of initial velocities", true);
		ParamDefTable[8].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=9, longName="spheres"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[9];
		ParamDef->init("spheres", TYPE_STRUCT, "ExplicitSpheres", true);






	}

	// Initialize DefinitionImpl node: nodeIndex=10, longName="spheres.positions"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[10];
		ParamDef->init("positions", TYPE_ARRAY, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("gameScale", "true", true);
		ParamDefTable[10].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("gameScale", "true", true);
		HintTable[1].init("shortDescription", "List of sphere positions", true);
		ParamDefTable[10].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */




		ParamDef->setArraySize(-1);
	}

	// Initialize DefinitionImpl node: nodeIndex=11, longName="spheres.positions[]"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[11];
		ParamDef->init("positions", TYPE_STRUCT, "SphereParams", true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("gameScale", "true", true);
		ParamDefTable[11].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("gameScale", "true", true);
		HintTable[1].init("shortDescription", "List of sphere positions", true);
		ParamDefTable[11].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=12, longName="spheres.positions[].center"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[12];
		ParamDef->init("center", TYPE_VEC3, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("gameScale", "true", true);
		ParamDefTable[12].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("gameScale", "true", true);
		HintTable[1].init("shortDescription", "Sphere centers", true);
		ParamDefTable[12].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=13, longName="spheres.positions[].radius"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[13];
		ParamDef->init("radius", TYPE_F32, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("gameScale", "true", true);
		HintTable[1].init("min", double(0.0f), true);
		ParamDefTable[13].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#else

		static HintImpl HintTable[3];
		static Hint* HintPtrTable[3] = { &HintTable[0], &HintTable[1], &HintTable[2], };
		HintTable[0].init("gameScale", "true", true);
		HintTable[1].init("min", double(0.0f), true);
		HintTable[2].init("shortDescription", "Sphere radiuses", true);
		ParamDefTable[13].setHints((const NvParameterized::Hint**)HintPtrTable, 3);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=14, longName="spheres.positions[].doDetectOverlaps"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[14];
		ParamDef->init("doDetectOverlaps", TYPE_BOOL, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("defaultValue", "false", true);
		ParamDefTable[14].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("defaultValue", "false", true);
		HintTable[1].init("shortDescription", "Avoid overlaps with other shapes?", true);
		ParamDefTable[14].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=15, longName="spheres.velocities"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[15];
		ParamDef->init("velocities", TYPE_ARRAY, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("gameScale", "true", true);
		ParamDefTable[15].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("gameScale", "true", true);
		HintTable[1].init("shortDescription", "List of initial velocities for particles in sphere", true);
		ParamDefTable[15].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */




		ParamDef->setArraySize(-1);
	}

	// Initialize DefinitionImpl node: nodeIndex=16, longName="spheres.velocities[]"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[16];
		ParamDef->init("velocities", TYPE_VEC3, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("gameScale", "true", true);
		ParamDefTable[16].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("gameScale", "true", true);
		HintTable[1].init("shortDescription", "List of initial velocities for particles in sphere", true);
		ParamDefTable[16].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=17, longName="ellipsoids"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[17];
		ParamDef->init("ellipsoids", TYPE_STRUCT, "ExplicitEllipsoids", true);






	}

	// Initialize DefinitionImpl node: nodeIndex=18, longName="ellipsoids.positions"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[18];
		ParamDef->init("positions", TYPE_ARRAY, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("gameScale", "true", true);
		ParamDefTable[18].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("gameScale", "true", true);
		HintTable[1].init("shortDescription", "List of ellipsoid positions", true);
		ParamDefTable[18].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */




		ParamDef->setArraySize(-1);
	}

	// Initialize DefinitionImpl node: nodeIndex=19, longName="ellipsoids.positions[]"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[19];
		ParamDef->init("positions", TYPE_STRUCT, "EllipsoidParams", true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("gameScale", "true", true);
		ParamDefTable[19].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("gameScale", "true", true);
		HintTable[1].init("shortDescription", "List of ellipsoid positions", true);
		ParamDefTable[19].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=20, longName="ellipsoids.positions[].center"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[20];
		ParamDef->init("center", TYPE_VEC3, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("gameScale", "true", true);
		ParamDefTable[20].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("gameScale", "true", true);
		HintTable[1].init("shortDescription", "Sphere centers", true);
		ParamDefTable[20].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=21, longName="ellipsoids.positions[].radius"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[21];
		ParamDef->init("radius", TYPE_F32, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("gameScale", "true", true);
		HintTable[1].init("min", double(0.0f), true);
		ParamDefTable[21].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#else

		static HintImpl HintTable[3];
		static Hint* HintPtrTable[3] = { &HintTable[0], &HintTable[1], &HintTable[2], };
		HintTable[0].init("gameScale", "true", true);
		HintTable[1].init("min", double(0.0f), true);
		HintTable[2].init("shortDescription", "Sphere radiuses", true);
		ParamDefTable[21].setHints((const NvParameterized::Hint**)HintPtrTable, 3);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=22, longName="ellipsoids.positions[].normal"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[22];
		ParamDef->init("normal", TYPE_VEC3, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Normal to equatorial planes", true);
		ParamDefTable[22].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=23, longName="ellipsoids.positions[].polarRadius"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[23];
		ParamDef->init("polarRadius", TYPE_F32, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("gameScale", "true", true);
		HintTable[1].init("min", double(0.0f), true);
		ParamDefTable[23].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#else

		static HintImpl HintTable[3];
		static Hint* HintPtrTable[3] = { &HintTable[0], &HintTable[1], &HintTable[2], };
		HintTable[0].init("gameScale", "true", true);
		HintTable[1].init("min", double(0.0f), true);
		HintTable[2].init("shortDescription", "Polar radius", true);
		ParamDefTable[23].setHints((const NvParameterized::Hint**)HintPtrTable, 3);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=24, longName="ellipsoids.positions[].doDetectOverlaps"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[24];
		ParamDef->init("doDetectOverlaps", TYPE_BOOL, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("defaultValue", "false", true);
		ParamDefTable[24].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("defaultValue", "false", true);
		HintTable[1].init("shortDescription", "Avoid overlaps with other shapes?", true);
		ParamDefTable[24].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=25, longName="ellipsoids.velocities"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[25];
		ParamDef->init("velocities", TYPE_ARRAY, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("gameScale", "true", true);
		ParamDefTable[25].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("gameScale", "true", true);
		HintTable[1].init("shortDescription", "List of initial velocities for particles in ellipsoid", true);
		ParamDefTable[25].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */




		ParamDef->setArraySize(-1);
	}

	// Initialize DefinitionImpl node: nodeIndex=26, longName="ellipsoids.velocities[]"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[26];
		ParamDef->init("velocities", TYPE_VEC3, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("gameScale", "true", true);
		ParamDefTable[26].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("gameScale", "true", true);
		HintTable[1].init("shortDescription", "List of initial velocities for particles in ellipsoid", true);
		ParamDefTable[26].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// SetChildren for: nodeIndex=0, longName=""
	{
		static Definition* Children[4];
		Children[0] = PDEF_PTR(1);
		Children[1] = PDEF_PTR(2);
		Children[2] = PDEF_PTR(9);
		Children[3] = PDEF_PTR(17);

		ParamDefTable[0].setChildren(Children, 4);
	}

	// SetChildren for: nodeIndex=2, longName="points"
	{
		static Definition* Children[2];
		Children[0] = PDEF_PTR(3);
		Children[1] = PDEF_PTR(7);

		ParamDefTable[2].setChildren(Children, 2);
	}

	// SetChildren for: nodeIndex=3, longName="points.positions"
	{
		static Definition* Children[1];
		Children[0] = PDEF_PTR(4);

		ParamDefTable[3].setChildren(Children, 1);
	}

	// SetChildren for: nodeIndex=4, longName="points.positions[]"
	{
		static Definition* Children[2];
		Children[0] = PDEF_PTR(5);
		Children[1] = PDEF_PTR(6);

		ParamDefTable[4].setChildren(Children, 2);
	}

	// SetChildren for: nodeIndex=7, longName="points.velocities"
	{
		static Definition* Children[1];
		Children[0] = PDEF_PTR(8);

		ParamDefTable[7].setChildren(Children, 1);
	}

	// SetChildren for: nodeIndex=9, longName="spheres"
	{
		static Definition* Children[2];
		Children[0] = PDEF_PTR(10);
		Children[1] = PDEF_PTR(15);

		ParamDefTable[9].setChildren(Children, 2);
	}

	// SetChildren for: nodeIndex=10, longName="spheres.positions"
	{
		static Definition* Children[1];
		Children[0] = PDEF_PTR(11);

		ParamDefTable[10].setChildren(Children, 1);
	}

	// SetChildren for: nodeIndex=11, longName="spheres.positions[]"
	{
		static Definition* Children[3];
		Children[0] = PDEF_PTR(12);
		Children[1] = PDEF_PTR(13);
		Children[2] = PDEF_PTR(14);

		ParamDefTable[11].setChildren(Children, 3);
	}

	// SetChildren for: nodeIndex=15, longName="spheres.velocities"
	{
		static Definition* Children[1];
		Children[0] = PDEF_PTR(16);

		ParamDefTable[15].setChildren(Children, 1);
	}

	// SetChildren for: nodeIndex=17, longName="ellipsoids"
	{
		static Definition* Children[2];
		Children[0] = PDEF_PTR(18);
		Children[1] = PDEF_PTR(25);

		ParamDefTable[17].setChildren(Children, 2);
	}

	// SetChildren for: nodeIndex=18, longName="ellipsoids.positions"
	{
		static Definition* Children[1];
		Children[0] = PDEF_PTR(19);

		ParamDefTable[18].setChildren(Children, 1);
	}

	// SetChildren for: nodeIndex=19, longName="ellipsoids.positions[]"
	{
		static Definition* Children[5];
		Children[0] = PDEF_PTR(20);
		Children[1] = PDEF_PTR(21);
		Children[2] = PDEF_PTR(22);
		Children[3] = PDEF_PTR(23);
		Children[4] = PDEF_PTR(24);

		ParamDefTable[19].setChildren(Children, 5);
	}

	// SetChildren for: nodeIndex=25, longName="ellipsoids.velocities"
	{
		static Definition* Children[1];
		Children[0] = PDEF_PTR(26);

		ParamDefTable[25].setChildren(Children, 1);
	}

	mBuiltFlag = true;

}
void EmitterGeomExplicitParams_0p1::initStrings(void)
{
}

void EmitterGeomExplicitParams_0p1::initDynamicArrays(void)
{
	points.positions.buf = NULL;
	points.positions.isAllocated = true;
	points.positions.elementSize = sizeof(PointParams_Type);
	points.positions.arraySizes[0] = 0;
	points.velocities.buf = NULL;
	points.velocities.isAllocated = true;
	points.velocities.elementSize = sizeof(physx::PxVec3);
	points.velocities.arraySizes[0] = 0;
	spheres.positions.buf = NULL;
	spheres.positions.isAllocated = true;
	spheres.positions.elementSize = sizeof(SphereParams_Type);
	spheres.positions.arraySizes[0] = 0;
	spheres.velocities.buf = NULL;
	spheres.velocities.isAllocated = true;
	spheres.velocities.elementSize = sizeof(physx::PxVec3);
	spheres.velocities.arraySizes[0] = 0;
	ellipsoids.positions.buf = NULL;
	ellipsoids.positions.isAllocated = true;
	ellipsoids.positions.elementSize = sizeof(EllipsoidParams_Type);
	ellipsoids.positions.arraySizes[0] = 0;
	ellipsoids.velocities.buf = NULL;
	ellipsoids.velocities.isAllocated = true;
	ellipsoids.velocities.elementSize = sizeof(physx::PxVec3);
	ellipsoids.velocities.arraySizes[0] = 0;
}

void EmitterGeomExplicitParams_0p1::initDefaults(void)
{

	freeStrings();
	freeReferences();
	freeDynamicArrays();

	initDynamicArrays();
	initStrings();
	initReferences();
}

void EmitterGeomExplicitParams_0p1::initReferences(void)
{
}

void EmitterGeomExplicitParams_0p1::freeDynamicArrays(void)
{
	if (points.positions.isAllocated && points.positions.buf)
	{
		mParameterizedTraits->free(points.positions.buf);
	}
	if (points.velocities.isAllocated && points.velocities.buf)
	{
		mParameterizedTraits->free(points.velocities.buf);
	}
	if (spheres.positions.isAllocated && spheres.positions.buf)
	{
		mParameterizedTraits->free(spheres.positions.buf);
	}
	if (spheres.velocities.isAllocated && spheres.velocities.buf)
	{
		mParameterizedTraits->free(spheres.velocities.buf);
	}
	if (ellipsoids.positions.isAllocated && ellipsoids.positions.buf)
	{
		mParameterizedTraits->free(ellipsoids.positions.buf);
	}
	if (ellipsoids.velocities.isAllocated && ellipsoids.velocities.buf)
	{
		mParameterizedTraits->free(ellipsoids.velocities.buf);
	}
}

void EmitterGeomExplicitParams_0p1::freeStrings(void)
{
}

void EmitterGeomExplicitParams_0p1::freeReferences(void)
{
}

} // namespace parameterized
} // namespace nvidia

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


#include "GroundEmitterActorParameters_0p0.h"
#include <string.h>
#include <stdlib.h>

using namespace NvParameterized;

namespace nvidia
{
namespace parameterized
{

using namespace GroundEmitterActorParameters_0p0NS;

const char* const GroundEmitterActorParameters_0p0Factory::vptr =
    NvParameterized::getVptr<GroundEmitterActorParameters_0p0, GroundEmitterActorParameters_0p0::ClassAlignment>();

const uint32_t NumParamDefs = 12;
static NvParameterized::DefinitionImpl* ParamDefTable; // now allocated in buildTree [NumParamDefs];


static const size_t ParamLookupChildrenTable[] =
{
	1, 4, 5, 6, 7, 8, 9, 10, 11, 2, 3,
};

#define TENUM(type) nvidia::##type
#define CHILDREN(index) &ParamLookupChildrenTable[index]
static const NvParameterized::ParamLookupNode ParamLookupTable[NumParamDefs] =
{
	{ TYPE_STRUCT, false, 0, CHILDREN(0), 9 },
	{ TYPE_STRUCT, false, (size_t)(&((ParametersStruct*)0)->densityRange), CHILDREN(9), 2 }, // densityRange
	{ TYPE_F32, false, (size_t)(&((rangeStructF32_Type*)0)->min), NULL, 0 }, // densityRange.min
	{ TYPE_F32, false, (size_t)(&((rangeStructF32_Type*)0)->max), NULL, 0 }, // densityRange.max
	{ TYPE_F32, false, (size_t)(&((ParametersStruct*)0)->radius), NULL, 0 }, // radius
	{ TYPE_VEC3, false, (size_t)(&((ParametersStruct*)0)->upDirection), NULL, 0 }, // upDirection
	{ TYPE_F32, false, (size_t)(&((ParametersStruct*)0)->raycastHeight), NULL, 0 }, // raycastHeight
	{ TYPE_F32, false, (size_t)(&((ParametersStruct*)0)->spawnHeight), NULL, 0 }, // spawnHeight
	{ TYPE_U32, false, (size_t)(&((ParametersStruct*)0)->maxRaycastsPerFrame), NULL, 0 }, // maxRaycastsPerFrame
	{ TYPE_STRING, false, (size_t)(&((ParametersStruct*)0)->raycastCollisionGroupMaskName), NULL, 0 }, // raycastCollisionGroupMaskName
	{ TYPE_VEC3, false, (size_t)(&((ParametersStruct*)0)->attachRelativePosition), NULL, 0 }, // attachRelativePosition
	{ TYPE_MAT34, false, (size_t)(&((ParametersStruct*)0)->globalPose), NULL, 0 }, // globalPose
};


bool GroundEmitterActorParameters_0p0::mBuiltFlag = false;
NvParameterized::MutexType GroundEmitterActorParameters_0p0::mBuiltFlagMutex;

GroundEmitterActorParameters_0p0::GroundEmitterActorParameters_0p0(NvParameterized::Traits* traits, void* buf, int32_t* refCount) :
	NvParameters(traits, buf, refCount)
{
	//mParameterizedTraits->registerFactory(className(), &GroundEmitterActorParameters_0p0FactoryInst);

	if (!buf) //Do not init data if it is inplace-deserialized
	{
		initDynamicArrays();
		initStrings();
		initReferences();
		initDefaults();
	}
}

GroundEmitterActorParameters_0p0::~GroundEmitterActorParameters_0p0()
{
	freeStrings();
	freeReferences();
	freeDynamicArrays();
}

void GroundEmitterActorParameters_0p0::destroy()
{
	// We cache these fields here to avoid overwrite in destructor
	bool doDeallocateSelf = mDoDeallocateSelf;
	NvParameterized::Traits* traits = mParameterizedTraits;
	int32_t* refCount = mRefCount;
	void* buf = mBuffer;

	this->~GroundEmitterActorParameters_0p0();

	NvParameters::destroy(this, traits, doDeallocateSelf, refCount, buf);
}

const NvParameterized::DefinitionImpl* GroundEmitterActorParameters_0p0::getParameterDefinitionTree(void)
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

const NvParameterized::DefinitionImpl* GroundEmitterActorParameters_0p0::getParameterDefinitionTree(void) const
{
	GroundEmitterActorParameters_0p0* tmpParam = const_cast<GroundEmitterActorParameters_0p0*>(this);

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

NvParameterized::ErrorType GroundEmitterActorParameters_0p0::getParameterHandle(const char* long_name, Handle& handle) const
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

NvParameterized::ErrorType GroundEmitterActorParameters_0p0::getParameterHandle(const char* long_name, Handle& handle)
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

void GroundEmitterActorParameters_0p0::getVarPtr(const Handle& handle, void*& ptr, size_t& offset) const
{
	ptr = getVarPtrHelper(&ParamLookupTable[0], const_cast<GroundEmitterActorParameters_0p0::ParametersStruct*>(&parameters()), handle, offset);
}


/* Dynamic Handle Indices */

void GroundEmitterActorParameters_0p0::freeParameterDefinitionTable(NvParameterized::Traits* traits)
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

void GroundEmitterActorParameters_0p0::buildTree(void)
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

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "This class is used for creating NxGroundEmitterActor instances", true);
		ParamDefTable[0].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=1, longName="densityRange"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[1];
		ParamDef->init("densityRange", TYPE_STRUCT, "rangeStructF32", true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "The ground emitter actor will use the maximum density in the range, but it will back off to the minimum density if the actor is LOD resource limited.\n", true);
		HintTable[1].init("shortDescription", "Density Range", true);
		ParamDefTable[1].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=2, longName="densityRange.min"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[2];
		ParamDef->init("min", TYPE_F32, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Minimum (scalar value)", true);
		ParamDefTable[2].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=3, longName="densityRange.max"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[3];
		ParamDef->init("max", TYPE_F32, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Maximum (scalar value)", true);
		ParamDefTable[3].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=4, longName="radius"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[4];
		ParamDef->init("radius", TYPE_F32, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("defaultValue", uint64_t(10), true);
		ParamDefTable[4].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[3];
		static Hint* HintPtrTable[3] = { &HintTable[0], &HintTable[1], &HintTable[2], };
		HintTable[0].init("defaultValue", uint64_t(10), true);
		HintTable[1].init("longDescription", "The ground emitter actor will create objects within a circle of size 'radius'.\n", true);
		HintTable[2].init("shortDescription", "Radius", true);
		ParamDefTable[4].setHints((const NvParameterized::Hint**)HintPtrTable, 3);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=5, longName="upDirection"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[5];
		ParamDef->init("upDirection", TYPE_VEC3, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "The ground emitter asset needs to know what direction is 'up'.\n", true);
		HintTable[1].init("shortDescription", "Up Direction", true);
		ParamDefTable[5].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=6, longName="raycastHeight"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[6];
		ParamDef->init("raycastHeight", TYPE_F32, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "The height from which the ground emitter will cast rays at terrain/objects opposite of the 'upDirection'.\n", true);
		HintTable[1].init("shortDescription", "Raycast Height", true);
		ParamDefTable[6].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=7, longName="spawnHeight"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[7];
		ParamDef->init("spawnHeight", TYPE_F32, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("defaultValue", uint64_t(0), true);
		ParamDefTable[7].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[3];
		static Hint* HintPtrTable[3] = { &HintTable[0], &HintTable[1], &HintTable[2], };
		HintTable[0].init("defaultValue", uint64_t(0), true);
		HintTable[1].init("longDescription", "The height above the ground to emit particles. If greater than 0, the ground emitter will refresh a disc above the player's position rather than refreshing a circle around the player's position.\n", true);
		HintTable[2].init("shortDescription", "Spawn Height", true);
		ParamDefTable[7].setHints((const NvParameterized::Hint**)HintPtrTable, 3);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=8, longName="maxRaycastsPerFrame"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[8];
		ParamDef->init("maxRaycastsPerFrame", TYPE_U32, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("defaultValue", "UINT32_MAX", true);
		ParamDefTable[8].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[3];
		static Hint* HintPtrTable[3] = { &HintTable[0], &HintTable[1], &HintTable[2], };
		HintTable[0].init("defaultValue", "UINT32_MAX", true);
		HintTable[1].init("longDescription", "The maximum raycasts per frame.\n", true);
		HintTable[2].init("shortDescription", "Maximum Raycasts per Frame", true);
		ParamDefTable[8].setHints((const NvParameterized::Hint**)HintPtrTable, 3);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=9, longName="raycastCollisionGroupMaskName"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[9];
		ParamDef->init("raycastCollisionGroupMaskName", TYPE_STRING, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "This name resolves to a 32-bit bitmask of collision groups for raycasts around the player.  \nIt is resolved by a call to the named resource provider using the 'NSCollisionGroupMask' \nand 'NSCollisionGroup128' namespaces.  If none is provided, the raycast will hit everything in the scene. \nThis avoids storing fragile enums in asset files.  \n", true);
		HintTable[1].init("shortDescription", "Raycast Collision Group Mask Name", true);
		ParamDefTable[9].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=10, longName="attachRelativePosition"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[10];
		ParamDef->init("attachRelativePosition", TYPE_VEC3, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "The ground emitter will offset this value from the attach actor position.\n", true);
		HintTable[1].init("shortDescription", "Attach Relative Position", true);
		ParamDefTable[10].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=11, longName="globalPose"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[11];
		ParamDef->init("globalPose", TYPE_MAT34, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "An identity rotation matrix will result in a +Y up ground emitter, provide a rotation if another orientation is desired.\n", true);
		HintTable[1].init("shortDescription", "The actor's pose", true);
		ParamDefTable[11].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// SetChildren for: nodeIndex=0, longName=""
	{
		static Definition* Children[9];
		Children[0] = PDEF_PTR(1);
		Children[1] = PDEF_PTR(4);
		Children[2] = PDEF_PTR(5);
		Children[3] = PDEF_PTR(6);
		Children[4] = PDEF_PTR(7);
		Children[5] = PDEF_PTR(8);
		Children[6] = PDEF_PTR(9);
		Children[7] = PDEF_PTR(10);
		Children[8] = PDEF_PTR(11);

		ParamDefTable[0].setChildren(Children, 9);
	}

	// SetChildren for: nodeIndex=1, longName="densityRange"
	{
		static Definition* Children[2];
		Children[0] = PDEF_PTR(2);
		Children[1] = PDEF_PTR(3);

		ParamDefTable[1].setChildren(Children, 2);
	}

	mBuiltFlag = true;

}
void GroundEmitterActorParameters_0p0::initStrings(void)
{
	raycastCollisionGroupMaskName.isAllocated = true;
	raycastCollisionGroupMaskName.buf = NULL;
}

void GroundEmitterActorParameters_0p0::initDynamicArrays(void)
{
}

void GroundEmitterActorParameters_0p0::initDefaults(void)
{

	freeStrings();
	freeReferences();
	freeDynamicArrays();

	densityRange.min = 1.0f;
	densityRange.max = 1.0f;

	radius = float(10.0f);
	upDirection = physx::PxVec3(init(0, 1, 0));
	raycastHeight = float(10.0f);
	spawnHeight = float(0.0f);
	maxRaycastsPerFrame = uint32_t(UINT32_MAX);
	attachRelativePosition = physx::PxVec3(init(0, 0, 0));
	{
		const float value[12] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0};
		for (int i = 0; i < 12; ++i)
		{
			globalPose[i] = value[i];
		}
	}

	initDynamicArrays();
	initStrings();
	initReferences();
}

void GroundEmitterActorParameters_0p0::initReferences(void)
{
}

void GroundEmitterActorParameters_0p0::freeDynamicArrays(void)
{
}

void GroundEmitterActorParameters_0p0::freeStrings(void)
{

	if (raycastCollisionGroupMaskName.isAllocated && raycastCollisionGroupMaskName.buf)
	{
		mParameterizedTraits->strfree((char*)raycastCollisionGroupMaskName.buf);
	}
}

void GroundEmitterActorParameters_0p0::freeReferences(void)
{
}

} // namespace parameterized
} // namespace nvidia

#ifndef UAD_PRIMITIVEBASE_H
#define UAD_PRIMITIVEBASE_H
#include "SceneProps.h"
class PrimitiveBase {
public:
	virtual void Create() = 0;
	virtual void Transform(float *t) = 0;
	virtual void Draw(float *t,float *vp) = 0;
	virtual void Destroy() = 0;
	virtual void SetDocName(char* docname)=0;
	virtual void setProps(SceneProps* props) = 0;
};


#endif
#include "RenderObject.h"
#include "../../Common/MeshGeometry.h"

using namespace NCL::CSC8503;
using namespace NCL;

RenderObject::RenderObject(Transform* parentTransform, MeshGeometry* mesh, TextureBase* tex, ShaderBase* shader) {
	this->transform	= parentTransform;
	this->mesh		= mesh;
	this->texture	= tex;
	this->shader	= shader;
	this->colour	= Vector4(1.0f, 1.0f, 1.0f, 1.0f);
}


RenderObject::RenderObject(MeshGeometry* mesh, TextureBase* tex, ShaderBase* shader) {
	this->mesh = mesh;
	this->texture = tex;
	this->shader = shader;
	this->colour = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
}

RenderObject::RenderObject(RenderObject* copyRender) {
	this->mesh = new OGLMesh();
	this->mesh = copyRender->mesh;
	this->texture = copyRender->texture;
	this->shader = copyRender->shader;
	this->colour = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
}

RenderObject::~RenderObject() {

}
#include "../OpenGLHeader.h"
#include "IRenderableActor.h"
#include "../RenderDevice.h"

namespace CForge {

	IRenderableActor::IRenderableActor(const std::string ClassName, int32_t ActorType): CForgeObject("IRenderableActor::" + ClassName) {
		m_TypeID = ActorType;
	}//Constructor

	IRenderableActor::~IRenderableActor(void) {

	}//Destructor

	int32_t IRenderableActor::typeID(void)const {
		return m_TypeID;
	}//typeID


	void IRenderableActor::setBufferData(void) {

		// bind array and index buffer
		m_VertexBuffer.bind();
		m_ElementBuffer.bind();

		// position array
		if (m_VertexUtility.hasProperties(VertexUtility::VPROP_POSITION)) {
			glEnableVertexAttribArray(GLShader::attribArrayIndex(GLShader::ATTRIB_POSITION));
			glVertexAttribPointer(GLShader::attribArrayIndex(GLShader::ATTRIB_POSITION), 3, GL_FLOAT, GL_FALSE, m_VertexUtility.vertexSize(), (const void*)(uint64_t(m_VertexUtility.offset(VertexUtility::VPROP_POSITION))));
		}

		// normal array
		if (m_VertexUtility.hasProperties(VertexUtility::VPROP_NORMAL)) {
			glEnableVertexAttribArray(GLShader::attribArrayIndex(GLShader::ATTRIB_NORMAL));
			glVertexAttribPointer(GLShader::attribArrayIndex(GLShader::ATTRIB_NORMAL), 3, GL_FLOAT, GL_FALSE, m_VertexUtility.vertexSize(), (const void*)(uint64_t(m_VertexUtility.offset(VertexUtility::VPROP_NORMAL))));
		}

		// tangent array
		if (m_VertexUtility.hasProperties(VertexUtility::VPROP_TANGENT)) {
			glEnableVertexAttribArray(GLShader::attribArrayIndex(GLShader::ATTRIB_TANGENT));
			glVertexAttribPointer(GLShader::attribArrayIndex(GLShader::ATTRIB_TANGENT), 3, GL_FLOAT, GL_FALSE, m_VertexUtility.vertexSize(), (const void*)(uint64_t(m_VertexUtility.offset(VertexUtility::VPROP_TANGENT))));
		}

		// texture coordinates
		if (m_VertexUtility.hasProperties(VertexUtility::VPROP_UVW)) {
			glEnableVertexAttribArray(GLShader::attribArrayIndex(GLShader::ATTRIB_UVW));
			glVertexAttribPointer(GLShader::attribArrayIndex(GLShader::ATTRIB_UVW), 3, GL_FLOAT, GL_FALSE, m_VertexUtility.vertexSize(), (const void*)(uint64_t(m_VertexUtility.offset(VertexUtility::VPROP_UVW))));
		}

		// vertex colors
		if (m_VertexUtility.hasProperties(VertexUtility::VPROP_COLOR)) {
			glEnableVertexAttribArray(GLShader::attribArrayIndex(GLShader::ATTRIB_COLOR));
			glVertexAttribPointer(GLShader::attribArrayIndex(GLShader::ATTRIB_COLOR), 3, GL_FLOAT, GL_FALSE, m_VertexUtility.vertexSize(), (const void*)(uint64_t(m_VertexUtility.offset(VertexUtility::VPROP_COLOR))));
		}

		if (m_VertexUtility.hasProperties(VertexUtility::VPROP_BONEINDICES)) {
			glEnableVertexAttribArray(GLShader::attribArrayIndex(GLShader::ATTRIB_BONE_INDICES));
			glVertexAttribIPointer(GLShader::attribArrayIndex(GLShader::ATTRIB_BONE_INDICES), 4, GL_INT, m_VertexUtility.vertexSize(), (const void*)(uint64_t(m_VertexUtility.offset(VertexUtility::VPROP_BONEINDICES))));
		}

		if (m_VertexUtility.hasProperties(VertexUtility::VPROP_BONEWEIGHTS)) {
			glEnableVertexAttribArray(GLShader::attribArrayIndex(GLShader::ATTRIB_BONE_WEIGHTS));
			glVertexAttribPointer(GLShader::attribArrayIndex(GLShader::ATTRIB_BONE_WEIGHTS), 4, GL_FLOAT, GL_FALSE, m_VertexUtility.vertexSize(), (const void*)(uint64_t(m_VertexUtility.offset(VertexUtility::VPROP_BONEWEIGHTS))));
		}
	}//setBufferData

	uint32_t IRenderableActor::materialCount(void) const {
		return m_RenderGroupUtility.renderGroupCount();
	}//materialCount

	RenderMaterial* IRenderableActor::material(uint32_t Index) {
		if (Index >= m_RenderGroupUtility.renderGroupCount()) throw IndexOutOfBoundsExcept("Index");
		return &(m_RenderGroupUtility.renderGroups()[Index]->Material);
	}//material

	const RenderMaterial* IRenderableActor::material(uint32_t Index)const {
		if (Index >= m_RenderGroupUtility.renderGroupCount()) throw IndexOutOfBoundsExcept("Index");
		return &m_RenderGroupUtility.renderGroup(Index)->Material;
	}//material

	BoundingVolume IRenderableActor::boundingVolume(void)const {
		return m_BV;
	}//boundingVolume

	void IRenderableActor::boundingVolume(const BoundingVolume BV) {
		if (BV.type() == BoundingVolume::TYPE_UNKNOWN) m_BV.clear();
		else if (BV.type() == BoundingVolume::TYPE_AABB) m_BV.init(BV.aabb());
		else if (BV.type() == BoundingVolume::TYPE_SPHERE) m_BV.init(BV.boundingSphere());
	}//boundingVolume



	Box IRenderableActor::getAABB()
	{
		return m_BV.aabb();
	}
	

	//TODO Deprecated, was part of LOD system, rework.
	void IRenderableActor::testAABBvis(RenderDevice* pRDev, Eigen::Matrix4f sgMat)
	{
	
	}

	bool IRenderableActor::isInstanced()
	{
		return m_isInstanced;
	}

	bool IRenderableActor::isManualInstanced()
	{
		return m_isManualInstaned;
	}

	bool IRenderableActor::isInLODSG() {
		return m_isInLODSG;
	}
	void IRenderableActor::setLODSG(bool inside) {
		m_isInLODSG = inside;
	}
	bool IRenderableActor::isInQueryContainer() {
		return m_isInQSG;
	}
	void IRenderableActor::setQSG(bool inside) {
		m_isInQSG = inside;
	}

	void IRenderableActor::bindLODLevel(uint32_t level) {

	}

	void IRenderableActor::addInstance(Eigen::Matrix4f matrix) {

	}

	void IRenderableActor::evaluateQueryResult(Eigen::Matrix4f mat, uint32_t pixelCount) {
	
	}

	void IRenderableActor::clearMatRef() {

	}

	float IRenderableActor::getAABBradius(const Eigen::Matrix4f& mat) {
		Eigen::Affine3f affine(mat);
		affine.data()[12] = 0.0;
		affine.data()[13] = 0.0;
		affine.data()[14] = 0.0;
		Eigen::Vector3f scaledAABBMax = affine * getAABB().max();
		Eigen::Vector3f scaledAABBMin = affine * getAABB().min();
		Eigen::Vector3f center = scaledAABBMin*0.5+scaledAABBMax*0.5;
		scaledAABBMax -= center;
		scaledAABBMin -= center;

		float aabbRadius = std::max(std::abs(scaledAABBMax.norm()), std::abs(scaledAABBMin.norm()));
		return aabbRadius;
	}
	//TODO END Deprecated, was part of LOD system, rework.
}//name space

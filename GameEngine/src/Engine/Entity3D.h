#ifndef ENTITY3D_H
#define ENTITY3D_H
#define EXPORTDLL _declspec(dllexport)

#include "glm/glm.hpp"
#include <vector>

struct Bounds
{
	float maxX = INT32_MIN;
	float maxY = INT32_MIN;
	float maxZ = INT32_MIN;
	float minX = INT32_MAX;
	float minY = INT32_MAX;
	float minZ = INT32_MAX;
};

struct VertexArray
{
	glm::vec3 actualVertexArray[8];
};

class EXPORTDLL Entity3D
{
public:
	Entity3D();
	Entity3D(glm::vec3 position, Entity3D* parent, class Shader* shader);
	~Entity3D();

	//transformations
	void Rotate(float angle, glm::vec3 axis);
	void Translate(float value, glm::vec3 axis);
	void Scale(glm::vec3 scaleValues);
	void SetPosition(glm::vec3 newPosition);
	glm::mat4 GetModel();
	void UpdateModelMatrix();
	virtual Bounds UpdateModelMatAndBoundingBox();
	void SetParent(Entity3D* parent);
	Entity3D* GetParent();
	virtual Shader* GetShader();
	std::vector<Entity3D*> & GetChilds();
	virtual Entity3D* GetNode(std::string node);
	static void SetSceneRoot(Entity3D* root);
	virtual void GetVertexPositions(std::vector<glm::vec3> &vertexVector) { return; }
	void CalculateBounds(std::vector<glm::vec3> vertices);
	Bounds CombineBounds(Bounds bounds1, Bounds bounds2);
	Bounds GenerateBoundsByVertex(VertexArray vertexArray);
	Bounds GenerateBoundsByTransformedVertex(VertexArray vArray, glm::mat4 modelMatrix);
	void SetVisibility(bool visible);
	
	class BoundingBox* GetBoundingBox();
	void SetColliderVisibility(bool visibility);
	bool GetColliderVisibility() const;
	virtual std::string GetName();
	virtual std::string GetTag();
	virtual bool isBSPPlane() const;
	bool isVisible = true;

protected:
	glm::vec3 position;
	glm::vec3 scale;
	glm::mat4 localModel;
	glm::mat4 worldModel;
	std::string name;
	std::string tag = "obj";
	Entity3D* parent;
	std::vector<Entity3D*> childs;
	Shader* shader;
	BoundingBox* regenerativeAABB;
	BoundingBox* staticBoundingBox;
	Bounds bounds;

private:
	static Entity3D* sceneRoot;

	friend class Model;
};

#endif

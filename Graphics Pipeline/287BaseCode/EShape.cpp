#include "EShape.h"

// Beginning of work for pipeline
EShapeData EShape::createEClosedCylinderY(const Material &mat, float R, float height, int slices) {
	EShapeData result;
	float angle = M_2PI / slices;
	for (int i = 0; i < slices; i++) {
		// cylinder
		// first point of cyl
		float x1 = R * glm::sin(i * angle);
		float y1 = 0.0f;
		float z1 = R * glm::cos(i * angle);
		// second point of cyl
		float x2 = R * glm::sin((i + 1) * angle);
		float y2 = 0.0f;
		float z2 = R * glm::cos((i + 1) * angle);
		// third point of cyl
		float x3 = R * glm::sin((i + 1) * angle);
		float y3 = height;
		float z3 = R * glm::cos((i + 1) * angle);
		// forth point of cyl
		float x4 = R * glm::sin(i * angle);
		float y4 = height;
		float z4 = R * glm::cos(i * angle);
		glm::vec3 n = normalFrom3Points(glm::vec3(x1, y1, z1), glm::vec3(x2, y2, z2), glm::vec3(x3, y3, z3)); 
		VertexData v1(glm::vec4(x1, y1, z1, 1), n, mat);
		VertexData v2(glm::vec4(x2, y2, z2, 1), n, mat);
		VertexData v3(glm::vec4(x3, y3, z3, 1), n, mat);
		VertexData v4(glm::vec4(x4, y4, z4, 1), n, mat);
		// tri one
		result.push_back(v1);
		result.push_back(v2);
		result.push_back(v3);
		// tri two
		result.push_back(v3);
		result.push_back(v4);
		result.push_back(v1);
		
		// top disk
		// first point of disk
		float x5 = 0.0f;
		float y5 = 0.0f;
		float z5 = 0.0f;
		// second point of disk
		float x6 = R * glm::sin(i * angle);
		float y6 = 0.0f;
		float z6 = R * glm::cos(i * angle);
		// third point of disk
		float x7 = R * glm::sin((i + 1) * angle);
		float y7 = 0.0f;
		float z7 = R * glm::cos((i + 1) * angle);
		n = normalFrom3Points(glm::vec3(x5, y5, z5), glm::vec3(x6, y6, z6), glm::vec3(x7, y7, z7)); 
		VertexData v5(glm::vec4(x5, y5, z5, 1), n, mat);
		VertexData v6(glm::vec4(x6, y6, z6, 1), n, mat);
		VertexData v7(glm::vec4(x7, y7, z7, 1), n, mat);
		// tri 
		result.push_back(v5);
		result.push_back(v6);
		result.push_back(v7);
		
		// bot disk
		// first point of disk
		float x8 = 0.0f;
		float y8 = height;
		float z8 = 0.0f;
		// second point of disk
		float x9 = R * glm::sin(i * angle);
		float y9 = height;
		float z9 = R * glm::cos(i * angle);
		// third point of disk
		float x10 = R * glm::sin((i + 1) * angle);
		float y10 = height;
		float z10 = R * glm::cos((i + 1) * angle);
		n = normalFrom3Points(glm::vec3(x8, y8, z8), glm::vec3(x9, y9, z9), glm::vec3(x10, y10, z10));
		VertexData v8(glm::vec4(x8, y8, z8, 1), n, mat);
		VertexData v9(glm::vec4(x9, y9, z9, 1), n, mat);
		VertexData v10(glm::vec4(x10, y10, z10, 1), n, mat);
		// tri 
		result.push_back(v8);
		result.push_back(v9);
		result.push_back(v10);
	}
	return result;
}
// End of work for pipeline

/**
 * @fn	EShapeData EShape::createEDisk(const Material &mat, float radius, int slices)
 * @brief	Creates a disk.
 * @param	mat   	Material.
 * @param	radius	Radius.
 * @param	slices	Number of slices.
 * @return	The new disk.
 */

EShapeData EShape::createEDisk(const Material &mat, float radius, int slices) {
	EShapeData result;
	float angle = M_2PI / slices;
	for (int i = 0; i < slices; i++) {
		// first point of disk
		float x1 = 0.0f;
		float y1 = 0.0f;
		float z1 = 0.0f;
		// second point of disk
		float x2 = radius * glm::sin(i * angle);
		float y2 = 0.0f;
		float z2 = radius * glm::cos(i * angle);
		// third point of disk
		float x3 = radius * glm::sin((i + 1) * angle);
		float y3 = 0.0f;
		float z3 = radius * glm::cos((i + 1) * angle);
		glm::vec3 n = normalFrom3Points(glm::vec3(x1, y1, z1), glm::vec3(x2, y2, z2), glm::vec3(x3, y3, z3)); // get the normal from three pts above
		VertexData v1(glm::vec4(x1, y1, z1, 1), n, mat);
		VertexData v2(glm::vec4(x2, y2, z2, 1), n, mat);
		VertexData v3(glm::vec4(x3, y3, z3, 1), n, mat);
		// tri 
		result.push_back(v1);
		result.push_back(v2);
		result.push_back(v3);
	}
	return result;
}

/**
 * @fn	EShapeData EShape::createEPyramid(const Material &mat, float width, float height)
 * @brief	Creates a pyramid with origin at (0,0,0) and pointing toward +y.
 * @param	mat   	Material.
 * @param	width 	Width.
 * @param	height	Height.
 * @return	The new pyramid.
 */

EShapeData EShape::createEPyramid(const Material &mat, float width, float height) {
	EShapeData verts;
	return verts;
}

/**
 * @fn	EShapeData EShape::createECylinder(const Material &mat, float radius, float height, int slices)
 * @brief	Creates cylinder, which is centered on (0,0,0) and aligned with y axis.
 * @param	mat   	Material.
 * @param	radius	Radius.
 * @param	height	Height.
 * @param	slices	Slices.
 * @param	stacks	Stacks.
 * @return	The new cylinder.
 */

EShapeData EShape::createECylinder(const Material &mat, float R, float height, int slices, int stacks) {
	EShapeData result;
	float angle = M_2PI / slices;
	for (int i = 0; i < slices; i++) {
		// first point of cyl
		float x1 = R * glm::sin(i * angle);
		float y1 = 0.0f;
		float z1 = R * glm::cos(i * angle);
		// second point of cyl
		float x2 = R * glm::sin((i + 1) * angle);
		float y2 = 0.0f;
		float z2 = R * glm::cos((i + 1) * angle);
		// third point of cyl
		float x3 = R * glm::sin((i + 1) * angle);
		float y3 = height;
		float z3 = R * glm::cos((i + 1) * angle);
		// forth point of cyl
		float x4 = R * glm::sin(i * angle);
		float y4 = height;
		float z4 = R * glm::cos(i * angle);
		glm::vec3 n = normalFrom3Points(glm::vec3(x1, y1, z1), glm::vec3(x2, y2, z2), glm::vec3(x3, y3, z3)); // get the normal from three pts above
		VertexData v1(glm::vec4(x1, y1, z1, 1), n, mat);
		VertexData v2(glm::vec4(x2, y2, z2, 1), n, mat);
		VertexData v3(glm::vec4(x3, y3, z3, 1), n, mat);
		VertexData v4(glm::vec4(x4, y4, z4, 1), n, mat);
		// tri one
		result.push_back(v1);
		result.push_back(v2);
		result.push_back(v3);
		// tri two
		result.push_back(v3);
		result.push_back(v4);
		result.push_back(v1);
	}
	return result;
}

/**
 * @fn	EShapeData EShape::createECone(const Material &mat, float radius, float height, int slices, int stacks)
 * @brief	Creates cone, which is aligned with y axis.
 * @param	mat   	Material.
 * @param	radius	Radius.
 * @param	height	Height.
 * @param	slices	Slices.
 * @param	stacks	Stacks.
 * @return	The new cone.
 */

EShapeData EShape::createECone(const Material &mat, float R, float height, int slices, int stacks) {
	EShapeData result;
	float angle = M_2PI / slices;
	for (int i = 0; i < slices; i++) {
		// first point of tri
		float x1 = R * glm::sin(i * angle);
		float y1 = 0.0f;
		float z1 = R * glm::cos(i * angle);
		// second point of tri
		float x2 = R * glm::sin((i + 1) * angle);
		float y2 = 0.0f;
		float z2 = R * glm::cos((i + 1) * angle);
		// third point of tri
		float x3 = 0;
		float y3 = height;
		float z3 = 0;
		glm::vec3 n = normalFrom3Points(glm::vec3(x1, y1, z1), glm::vec3(x2, y2, z2), glm::vec3(x3, y3, z3)); // get the normal from three pts above
		VertexData v1(glm::vec4(x1, y1, z1, 1), n, mat);
		VertexData v2(glm::vec4(x2, y2, z2, 1), n, mat);
		VertexData v3(glm::vec4(x3, y3, z3, 1), n, mat);
		result.push_back(v1);
		result.push_back(v2);
		result.push_back(v3);
	}
	return result;
}

/**
 * @fn	EShapeData EShape::createECube(const Material &mat, float width, float height, float depth)
 * @brief	Creates cube
 * @param	mat   	Material.
 * @param	width 	Width.
 * @param	height	Height.
 * @param	depth 	Depth.
 * @return	The new cube.
 */

EShapeData EShape::createECube(const Material &mat, float width, float height, float depth) {
	EShapeData result;
	return result;
}

/**
 * @fn	EShapeData EShape::createETriangles(const Material &mat, const std::vector<glm::vec4> &V)
 * @brief	Creates triangles
 * @param	mat	Material.
 * @param	V  	Vector of objects to process.
 * @return	The new triangles.
 */

EShapeData EShape::createETriangles(const Material &mat, const std::vector<glm::vec4> &V) {
	EShapeData result;
	size_t numTris = V.size() / 3;
	for (unsigned int i = 0; i < numTris; i++) {
		int start = 3 * i;
		const glm::vec4 &A = V[start];
		const glm::vec4 &B = V[start + 1];
		const glm::vec4 &C = V[start + 2];
		VertexData::addTriVertsAndComputeNormal(result, A, B, C, mat);
	}
	return result;
}

/**
 * @fn	EShapeData EShape::createEPlanes(const Material &mat, const std::vector<glm::vec4> &V)
 * @brief	Creates planes, which are defined by 4 corners.
 * @param	mat	Material.
 * @param	V  	Vector of points to process.
 * @return	The new planes.
 */

EShapeData EShape::createEPlanes(const Material &mat, const std::vector<glm::vec4> &V) {
	EShapeData result;
	size_t numPlanes = V.size() / 4;
	for (unsigned int i = 0; i < numPlanes; i++) {
		int start = 4 * i;
		const glm::vec4 &A = V[start];
		const glm::vec4 &B = V[start + 1];
		const glm::vec4 &C = V[start + 2];
		const glm::vec4 &D = V[start + 3];
		VertexData::addConvexPolyVertsAndComputeNormals(result, A, B, C, D, mat);
	}
	return result;
}

/**
 * @fn	EShapeData EShape::createELines(const Material &mat, const std::vector<glm::vec4> &V)
 * @brief	Creates lines
 * @param	mat	Material.
 * @param	V  	A vector of point-pairs.
 * @return	The new lines.
 */

EShapeData EShape::createELines(const Material &mat, const std::vector<glm::vec4> &V) {
	EShapeData result;
	for (unsigned int i = 0; i < V.size(); i++) {
		result.push_back(VertexData(V[i], ZEROVEC, mat));
	}
	return result;
}

/**
 * @fn	EShapeData EShape::createECheckerBoard(const Material &mat1, const Material &mat2, float WIDTH, float HEIGHT, int DIV)
 * @brief	Creates checker board pattern.
 * @param	mat1  	Material #1.
 * @param	mat2  	Material #2.
 * @param	WIDTH 	Width of overall plane.
 * @param	HEIGHT	Height of overall plane.
 * @param	DIV   	Number of divisions.
 * @return	The vertices in the checker board.
 */

EShapeData EShape::createECheckerBoard(const Material &mat1, const Material &mat2, float WIDTH, float HEIGHT, int DIV) {
	EShapeData result;

	const float INC = (float)WIDTH / DIV;
	for (int X = 0; X < DIV; X++) {
		bool isMat1 = X % 2 == 0;
		for (float Z = 0; Z < DIV; Z++) {
			glm::vec4 V0(-WIDTH / 2.0f + X*INC, 0.0f, -WIDTH / 2 + Z*INC, 1.0f);
			glm::vec4 V1 = V0 + glm::vec4(0.0f, 0.0f, INC, 0.0f);
			glm::vec4 V2 = V0 + glm::vec4(INC, 0.0f, INC, 0.0f);
			glm::vec4 V3 = V0 + glm::vec4(INC, 0.0f, 0.0f, 0.0f);
			const Material &mat = isMat1 ? mat1 : mat2;

			result.push_back(VertexData(V0, Y_AXIS, mat));
			result.push_back(VertexData(V1, Y_AXIS, mat));
			result.push_back(VertexData(V2, Y_AXIS, mat));

			result.push_back(VertexData(V2, Y_AXIS, mat));
			result.push_back(VertexData(V3, Y_AXIS, mat));
			result.push_back(VertexData(V0, Y_AXIS, mat));
			isMat1 = !isMat1;
		}
	}
	return result;
}

EShapeData EShape::createEMyPlane(const Material &mat, float halfOfWidth, float halfOfLength) {
	EShapeData result;

	// first point of rectangular flat plane
	float x1 = -halfOfWidth;
	float y1 = 0.0f;
	float z1 = halfOfLength;
	// second point of rectangular flat plane
	float x2 = halfOfWidth;
	float y2 = 0.0f;
	float z2 = halfOfLength;
	// third point of rectangular flat plane
	float x3 = halfOfWidth;
	float y3 = 0.0f;
	float z3 = -halfOfLength;
	// forth point of rectangular flat plane
	float x4 = -halfOfWidth;
	float y4 = 0.0f;
	float z4 = -halfOfLength;
	//glm::vec3 n = normalFrom3Points(glm::vec3(x1, y1, z1), glm::vec3(x2, y2, z2), glm::vec3(x3, y3, z3)); 
	// normal vector would be y axis
	VertexData v1(glm::vec4(x1, y1, z1, 1), Y_AXIS, mat);
	VertexData v2(glm::vec4(x2, y2, z2, 1), Y_AXIS, mat);
	VertexData v3(glm::vec4(x3, y3, z3, 1), Y_AXIS, mat);
	VertexData v4(glm::vec4(x4, y4, z4, 1), Y_AXIS, mat);
	result.push_back(v1);
	result.push_back(v2);
	result.push_back(v3);

	result.push_back(v3);
	result.push_back(v4);
	result.push_back(v1);

	return result;
}

/**
 * @fn	std::vector<VertexData> createSidePanel(const Material &mat, const glm::vec2 &V1, const glm::vec2 &V2)
 * @brief	Creates side panel for an extrusion.
 * @param	mat	Material.
 * @param	V1 	The first vertex of the side panel.
 * @param	V2 	The second vertex of the side panel.
 * @return	The vertices in the new side panel.
 */

static std::vector<VertexData> createSidePanel(const Material &mat, const glm::vec2 &V1, const glm::vec2 &V2) {
	std::vector<VertexData> verts;
	return verts;
}

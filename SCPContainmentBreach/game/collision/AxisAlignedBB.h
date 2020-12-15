#ifndef HF_AABB
#define HF_AABB

#include "../../math/Vector3.h"

class AxisAlignedBB {
public:
	float minX, minY, minZ;
	float maxX, maxY, maxZ;

	AxisAlignedBB() : minX(0), minY(0), minZ(0), maxX(0), maxY(0), maxZ(0) {}

	AxisAlignedBB(float miX, float miY, float miZ, float maX, float maY, float maZ) {
		minX = miX; minY = miY; minZ = miZ;
		maxX = maX; maxY = maY; maxZ = maZ;
	}

	AxisAlignedBB(Point min, Point max) {
		minX = min.x; minY = min.y; minZ = min.z;
		maxX = max.x; maxY = max.y; maxZ = max.z;
	}

	void SetBounds(float miX, float miY, float miZ, float maX, float maY, float maZ) {
		minX = miX; minY = miY; minZ = miZ;
		maxX = maX; maxY = maY; maxZ = maZ;
	}

	void SetAABB(AxisAlignedBB aabb) {
		SetBounds(aabb.minX, aabb.minY, aabb.minZ, aabb.maxX, aabb.maxY, aabb.maxZ);
	}

	// Sets the minimums and maximums based on the center coordinates and scale
	void SetPositionFromCenter(Point position, Size scale) {
		SetBounds(
			position.x - (scale.x),
			position.y - (scale.y),
			position.z - (scale.z),
			position.x + (scale.x),
			position.y + (scale.y),
			position.z + (scale.z)
		);
	}

	// Gets the center of the AABB based on its minimums and maximums
	Point GetCenter() {
		float sX = GetSizeX();
		float sY = GetSizeY();
		float sZ = GetSizeZ();

		return Point(
			minX + (sX / 2),
			minY + (sY / 2),
			minZ + (sZ / 2)
		);
	}

	AxisAlignedBB Copy() {
		return AxisAlignedBB(minX, minY, minZ, maxX, maxY, maxZ);
	}

	void Expand(float x, float y, float z) {
		minX -= x; minY -= y; minZ -= z;
		maxX += x; maxY += y; maxZ += z;
	}

	void Offset(float x, float y, float z) {
		minX += x; minY += y; minZ += z;
		maxX += x; maxY += y; maxZ += z;
	}

	float GetIntersectionAmountX(const AxisAlignedBB aabb, bool checkIntersection) {
		if (checkIntersection) {
			if (!IsAABBIntersectingAABB(aabb)) {
				return 0;
			}
		}
		if (minX < aabb.maxX && aabb.minX < minX) {
			return aabb.maxX - minX;
		}
		if (maxX > aabb.minX && aabb.minX > minX) {
			return maxX - aabb.minX;
		}
		return 0;
	}

	float GetIntersectionAmountY(const AxisAlignedBB aabb, bool checkIntersection) {
		if (checkIntersection) {
			if (!IsAABBIntersectingAABB(aabb)) {
				return 0;
			}
		}
		if (minY < aabb.maxY && aabb.minY < minY) {
			return aabb.maxY - minY;
		}
		if (maxY > aabb.minY && aabb.minY > minY) {
			return maxY - aabb.minY;
		}
		return 0;
	}

	float GetIntersectionAmountZ(const AxisAlignedBB aabb, bool checkIntersection) {
		if (checkIntersection) {
			if (!IsAABBIntersectingAABB(aabb)) {
				return 0;
			}
		}
		if (minZ < aabb.maxZ && aabb.minZ < minZ) {
			return aabb.maxZ - minZ;
		}
		if (maxZ > aabb.minZ && aabb.minZ > minZ) {
			return maxZ - aabb.minZ;
		}
		return 0;
	}

	bool IsAABBIntersectingAABB(AxisAlignedBB aabb) {
		return
			IntersectsAABBX(aabb) &&
			IntersectsAABBY(aabb) &&
			IntersectsAABBZ(aabb);
	}

	bool IsVectorIntersectingAABB(Point p) {
		return
			(p.x > minX && p.x < maxX) &&
			(p.y > minY && p.y < maxY) &&
			(p.z > minZ && p.z < maxZ);
	}

	Vector3 GetIntersection(AxisAlignedBB aabb) {
		return
			Vector3(
				GetIntersectionAmountX(aabb, false),
				GetIntersectionAmountY(aabb, false),
				GetIntersectionAmountZ(aabb, false)
			);
	}

	bool IsAABBVecIntersecting(Vector3 intersection) {
		return intersection.x != 0.0f && intersection.y != 0.0f && intersection.z != 0.0f;
	}


	float GetAverageEdgeLength() {
		float x = maxX - minX;
		float y = maxY - minY;
		float z = maxZ - minZ;
		return (x + y + z) / 3.0f;
	}

	// returns true if the X axis intersects a given AABB's X axis
	bool IntersectsAABBX(AxisAlignedBB aabb) {
		return aabb.maxX > minX && aabb.minX < maxX;
	}

	// returns true if the Y axis intersects a given AABB's Y axis
	bool IntersectsAABBY(AxisAlignedBB aabb) {
		return aabb.maxY > minY && aabb.minY < maxY;
	}

	// returns true if the Z axis intersects a given AABB's Z axis
	bool IntersectsAABBZ(AxisAlignedBB aabb) {
		return aabb.maxZ > minZ && aabb.minZ < maxZ;
	}

	Point GetMinimum() { return Point(minX, minY, minZ); }
	Point GetMaximum() { return Point(maxX, maxY, maxZ); }

	float GetSizeX() { return IsDirectionFlippedX() ? minX - maxX : maxX - minX; }
	float GetSizeY() { return IsDirectionFlippedY() ? minY - maxY : maxY - minY; }
	float GetSizeZ() { return IsDirectionFlippedZ() ? minZ - maxZ : maxZ - minZ; }
	Size GetSize() { return Size(GetSizeX(), GetSizeY(), GetSizeZ()); }

	bool MaxOverlapsAABBMinX(AxisAlignedBB aabb) { return maxX > aabb.minX; }
	bool MinOverlapsAABBMaxX(AxisAlignedBB aabb) { return minX < aabb.maxX; }
	bool MaxOverlapsAABBMinY(AxisAlignedBB aabb) { return maxY > aabb.minY; }
	bool MinOverlapsAABBMaxY(AxisAlignedBB aabb) { return minY < aabb.maxY; }
	bool MaxOverlapsAABBMinZ(AxisAlignedBB aabb) { return maxZ > aabb.minZ; }
	bool MinOverlapsAABBMaxZ(AxisAlignedBB aabb) { return minZ < aabb.maxZ; }

	bool IsBehindAABBX(AxisAlignedBB aabb) { return maxX < aabb.maxX&& minX < aabb.minX; }
	bool IsBehindAABBY(AxisAlignedBB aabb) { return maxY < aabb.maxY&& minY < aabb.minY; }
	bool IsBehindAABBZ(AxisAlignedBB aabb) { return maxZ < aabb.maxZ&& minZ < aabb.minZ; }


	static AxisAlignedBB CreateAABBFromCenter(Point position, Size scale) {
		AxisAlignedBB aabb;
		aabb.SetPositionFromCenter(position, scale);
		return aabb;
	}

	static AxisAlignedBB CreateAABB(Point min, Point max) {
		AxisAlignedBB aabb = AxisAlignedBB(min, max);
		return aabb;
	}

private:
	bool IsDirectionFlippedX() { return minX > maxX; }
	bool IsDirectionFlippedY() { return minY > maxY; }
	bool IsDirectionFlippedZ() { return minZ > maxZ; }
};

#endif // !HF_AABB
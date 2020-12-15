#ifndef HF_LAYERMASK
#define HF_LAYERMASK

/// <summary>
/// Used for determining whether a collider should collide with another collider.
/// If the 2 layers are the same, collisions dont happen
/// </summary>
typedef enum {
	A00 = 0,
	A01 = 1,
	A02 = 2,
	A03 = 3,
	A04 = 4,
	A05 = 5,
	A06 = 6,
	A07 = 7,
	A08 = 8,
	A09 = 9,
	A10 = 10,
	A11 = 11,
	A12 = 12,
	A13 = 13,
	A14 = 14,
	A15 = 15,
	A16 = 16,
	A17 = 17,
	A18 = 18,
	A19 = 19,
	A20 = 20,
	A21 = 21,
	A22 = 22,
	A23 = 23,
	A24 = 24,
	A25 = 25,
	A26 = 26,
	A27 = 27,
	A28 = 28,
	A29 = 29,
	A30 = 30,
	A31 = 31,
	A32 = 32,
	A33 = 33,
	A34 = 34,
	A35 = 35,
	A36 = 36,
	A37 = 37,
	A38 = 38,
	A39 = 39,
} ColliderMask;

#endif
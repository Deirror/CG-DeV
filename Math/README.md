# Math Operations

- This file explains what happens **in object space** — the local coordinate system of a 3D model — both **algebraically** (with linear algebra).

---

### What Is Object Space?

- **Object space** (also called *model space*) is the coordinate system **local to a 3D object**, before any transformations are applied to place it in the world.

- Each vertex is defined relative to the object’s **own origin** (0, 0, 0).
- Transformations here affect the model’s **shape, orientation, and local positioning**.
- The object’s local axes define its **forward**, **up**, and **right** directions.

---

Algebraic (Mathematical) Transformations
-

All transformations in object space are represented using **vectors and matrices**.

| Operation | Formula | Description |
|------------|----------|-------------|
| **Translation** | `p' = p + t` | Moves all vertices by offset `t = (tx, ty, tz)` |
| **Scaling** | `p' = S * p` | Scales by `S = diag(sx, sy, sz)` relative to origin |
| **Rotation** | `p' = R * p` | Rotates by rotation matrix `R`, often built from Euler angles or quaternions |
| **Shear** | `p' = H * p` | Skews object along one or more axes |
| **Reflection** | `p' = M * p` | Flips the object across a chosen axis or plane |
| **Affine Transform** | `p' = M * p + t` | Combines rotation, scaling, and translation |

> In practice, all of the above are combined into a single **4×4 homogeneous matrix**.

---

### Transformation Hierarchy

Transformations occur in this order:

1. **Object Space → World Space**
   - Apply the model (object-to-world) matrix.
2. **World Space → View Space**
   - Apply the camera (world-to-view) matrix.
3. **View Space → Clip Space**
   - Apply the projection matrix.

---

### ️Practical Notes

- The **order of matrix multiplication** matters (especially in column-major vs row-major conventions).
- Rotations happen **around the object’s pivot**, not the world origin.
- Object space is ideal for:
  - Vertex skinning (before world transforms)
  - Normals and tangent space computations
  - Local editing and procedural generation

---

### Summary

| Space | Definition | Typical Use |
|--------|-------------|--------------|
| **Object Space** | Coordinates relative to the model’s own origin | Modeling, deformation, local animation |
| **World Space** | Object placed in the scene | Positioning, collisions |
| **View Space** | Scene relative to camera | Lighting, clipping |
| **Clip Space** | Projected for rendering | Rasterization pipeline |
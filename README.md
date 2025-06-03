# OpenGL Collection

Description
-

- This repo contains some computer graphics development(*CGD*) projects, using ***OpenGL***
- It aims to share my work on such things and how to apply math to solve real-world problems
- Also I will paste some explanations about some parts of the process

Shaders
-

| GLSL Keyword           | What it does                                     |
| ---------------------- | ------------------------------------------------ |
| `in` (vertex)          | Input from vertex buffer layout.                 |
| `out` (vertex)         | Output passed to fragment shader.                |
| `in` (fragment)        | Input interpolated from vertex shader outputs.   |
| `uniform`              | External, constant input set by CPU-side OpenGL. |
| `gl_Position`          | Built-in; sets the final position of a vertex.   |
| `layout(location = N)` | Explicitly binds input/output locations.         |

- Vertex shader:
  -  Receives per-vertex data (in from buffer)
  - Applies transforms -> gl_Position
  - Outputs extra data (out) for the fragment shader

- Fragment shader:
  - Receives interpolated data (in)
  - Looks up textures, lighting, etc
  - Outputs vec4 color

- CPU-side:
  - Binds shaders, sets uniforms
  - Draws indexed vertices
  - Swaps buffers

Matrix Transformations
-

The rendering engine uses standard matrix transformations in OpenGL to position and orient 3D geometry in the scene. The core matrix pipeline follows the **Model-View-Projection (MVP)** pattern:

```cpp
glm::mat4 mvp = projection * view * model;
```

### Model Matrix

The model matrix transforms an object from local object space to world space. It includes transformations like:

- Translation – moves the object to a specific position in the world.
- Rotation – orients the object around one or more axes.

Scaling (not used in this code, but part of standard transformation)

Example:

```cpp
glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, -3.0f));
glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), rotationAngle, glm::vec3(1.0f, 0.0f, 0.0f));
glm::mat4 model = translation * rotation;
```

### View Matrix

The view matrix positions and orients the camera in the world. This is achieved using glm::lookAt, which constructs the view matrix from:

### Camera position

Target point (where the camera is looking)

- Up direction

Example:

```cpp
glm::mat4 view = glm::lookAt(
    cameraPos,
    cameraPos + cameraFront,
    cameraUp
);
```

### Projection Matrix

The projection matrix defines how the 3D scene is projected onto the 2D screen. This engine uses a perspective projection:

```cpp
glm::mat4 projection = glm::perspective(
    glm::radians(60.0f),  // field of view
    aspectRatio,          // width / height
    0.1f,                 // near plane
    10.0f                 // far plane
);
```

### MVP Composition

The final MVP matrix is computed as:

```cpp
glm::mat4 mvp = projection * view * model;
```

This composite matrix is sent to the shader to transform vertex positions from model space all the way to clip space for rasterization.

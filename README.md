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

OpenGL Buffer Objects
-

Modern OpenGL uses buffer objects to efficiently manage vertex data and rendering configuration. The main buffer types used in this engine are:

- **VAO** – Vertex Array Object
- **VBO** – Vertex Buffer Object
- **IBO** (also called EBO) – Index Buffer Object
- **VBLO** – Vertex Buffer Layout Object (not part of OpenGL core, but often used in abstraction layers)

### Vertex Buffer Object (VBO)

A **VBO** stores vertex attribute data (such as position, color, normals, etc.) in GPU memory. This allows the GPU to access the data directly during rendering without needing to re-upload it from the CPU each frame.

Typical usage:

```cpp
glGenBuffers(1, &vbo);
glBindBuffer(GL_ARRAY_BUFFER, vbo);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
```

- GL_ARRAY_BUFFER is used for vertex attributes
- GL_STATIC_DRAW hints that the data won't change often

### Vertex Array Object (VAO)
A VAO stores the configuration of vertex attribute pointers and buffer bindings. It acts like a container that remembers which VBOs and attribute layouts to use during drawing.

Typical usage:

```cpp
glGenVertexArrays(1, &vao);
glBindVertexArray(vao);

// Bind and configure VBO
glBindBuffer(GL_ARRAY_BUFFER, vbo);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
glEnableVertexAttribArray(0);
```

VAOs simplify rendering by letting you bind a single VAO before drawing, rather than setting up all attributes every frame.

### Index Buffer Object (IBO or EBO)

An IBO (or EBO – Element Buffer Object) stores indices into the vertex array, allowing reuse of vertex data and reducing redundancy.

Typical usage:

```cpp
glGenBuffers(1, &ibo);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
```

During rendering:

```cpp
glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
```

This draws geometry using indices from the IBO instead of relying on vertex order in the VBO.

### Vertex Buffer Layout Object (VBLO)

A VBLO is not part of OpenGL itself but is commonly used in abstraction layers to describe how vertex attributes are structured inside a VBO.

A VBLO helps:

- Define the layout (e.g., position at offset 0, color at offset 12)
- Automate calls to glVertexAttribPointer

For example, a layout definition might look like:

```cpp
layout.push<float>(3); // Position (x, y, z)
layout.push<float>(3); // Color (r, g, b)
layout.push<float>(2); // Texture coordinates (u, v)
```

This layout would then be applied during VAO/VBO setup, simplifying attribute bindings.

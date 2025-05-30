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
  - Applies transforms → gl_Position
  - Outputs extra data (out) for the fragment shader

- Fragment shader:
  - Receives interpolated data (in)
  - Looks up textures, lighting, etc
  - Outputs vec4 color

- CPU-side:
  - Binds shaders, sets uniforms
  - Draws indexed vertices
  - Swaps buffers

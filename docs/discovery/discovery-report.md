# Discovery report

## Problem statement

An animation studio needs a film renderer that it owns and that its own team can understand and fix, because its Maya renders now show black artifacts and take twice as long while licences cost about 2 million a year, but it has no rendering code, version control or documentation of its own, so nobody in the studio can explain or fix a broken render without depending on an outside vendor.

## Client interview summary

I could not attend today's class, so I asked my mates for the questions they asked and the client's answers.

### Current tooling and its failures

**Need:** The studio needs to understand why its current renders fail.

> **Q** (asked by a classmate): What do you use to render your films today?
>
> **A:** "Maya." Many machines run Maya only for rendering; about 10 licences are used for modelling.

> **Q** (asked by a classmate): What was the problem with the last software?
>
> **A:** Black artifacts appeared in the images and render time doubled, starting about 6 months ago on a big project.

> **Q** (asked by a classmate): How is your code documented? Do you use version control?
>
> **A:** "There is no documentation format." No code manager like Git.

**My conclusion:** The biggest issue is the lack of documentation. Also, since only about 10 licences are used for modelling, does the studio still need the other Maya licences once rendering is replaced?

### Cost and ownership

**Need:** The studio needs to cut its licence costs and own its renderer.

> **Q** (asked by a classmate): Why not buy an existing render engine?
>
> **A:** Licences are too expensive: about 2 million a year, paid per computer.

> **Q** (asked by a classmate): Free engines exist (Cycles, pbrt, LuxCoreRender). Why not extend one?
>
> **A:** Waiting for a community to fix bugs has been slow. "We want to be the owner of the ray tracer."

> **Q** (asked by a classmate): What would you like to do that you couldn't before?
>
> **A:** "Add our own features."

> **Q** (asked by a classmate): Any constraint on the licence of the tools we use?
>
> **A:** "Open source."

**My conclusion:** Existing licences are too expensive. The libraries we use must be open source, and the studio must own the renderer.

### Trust and maintenance

**Need:** The studio needs to maintain the renderer itself, over the long term.

> **Q** (asked by the interviewer): What would make you stop trusting the tool?
>
> **A:** "To trust the solution we want to know why a bug happened and be able to resolve it."

> **Q** (asked by the interviewer): Who will maintain this in five years?
>
> **A:** In-house, long term, with partner studios' skills.

**My conclusion:** The project must be well documented and maintained in-house.

### Rendering requirements

**Need:** The studio needs to render full animated films fast enough to meet its schedule.

> **Q** (asked by the interviewer): What kind of content do you render?
>
> **A:** "Full animation" films, like Toy Story.

> **Q** (asked by a classmate): What quality do you expect?
>
> **A:** "HD", a "reliable image", at 24 FPS.

> **Q** (asked by the interviewer): When does a frame take too long?
>
> **A:** "1 minute is long for a frame rendering and 10 min is too much." "The faster the better."

> **Q** (asked by a classmate): How long can rendering a film take?
>
> **A:** A 90-minute film must be rendered in about 2 months, with about 10 pre-renders per image.

> **Q** (asked by a classmate): Where do renders run?
>
> **A:** On a CPU render farm.

**My conclusion:** We need to render HD animated films at 24 FPS, with each frame taking less than a minute. A film of about 90 minutes must be rendered in under 2 months. Renders run on a CPU farm.

### Project constraints

**Need:** The studio needs the project delivered within its budget and deadline.

> **Q** (asked by a classmate): What is the budget?
>
> **A:** 500 000.

> **Q** (asked by a classmate): When is the deadline?
>
> **A:** January.

**My conclusion:** A budget of 500k (currency to confirm) for about 2-3 months, from mid-November to January.

### Open questions

- Farm size: "100 CPU" or "1000 computers"? 100 machines or 100 cores?
- Deadline: 5 or 15 January? Does the 2-month render window start after delivery?
- Currency of the budget and licence cost: euros or dollars?
- HD: 720p or 1080p?
- Which scene file format, exported by which tool?
- Does "reliable image" mean identical output on every run?
- Who in the studio can maintain C++ code, with no Git and no documentation today?

## State of the art

| Solution | Maker | Licence | Pricing (date checked) | Capabilities | Sources |
|---|---|---|---|---|---|
| RenderMan | Pixar | Proprietary (free non-commercial version) | $595 per licence + $250/year maintenance; rental $5/licence/day (min. 10 licences, 7 days) (2026-11-16) | Production path tracer used for Pixar films; one licence = one artist seat or one render node | [Pixar store](https://renderman.pixar.com/store) |
| Arnold | Autodesk | Proprietary, subscription | ~$400–430/year single-user, ~$630–750/year multi-user, reseller prices (Autodesk page not reachable) (2026-11-16) | Monte Carlo path tracer, CPU and GPU, bundled with Maya | [Novedge](https://novedge.com/products/buy-arnold-subscription), [MotionMedia](https://www.motionmedia.com/autodesk-arnold/) |
| V-Ray | Chaos | Proprietary, subscription | Solo $540/year; Premium $778.80/year (floating) (2026-11-16) | CPU and GPU renderer, plugins for Maya, 3ds Max and others | [Chaos](https://www.chaos.com/vray) |
| Cycles | Blender Foundation | Apache 2.0 | Free | Physically based production renderer, embeddable in other software | [cycles-renderer.org](https://www.cycles-renderer.org/), [GitHub](https://github.com/blender/cycles) |
| pbrt-v4 | Pharr, Jakob, Humphreys | Apache 2.0 | Free (book free online) | Research/teaching renderer, spectral rendering, GPU path; Academy Award 2014 | [pbrt.org](https://pbrt.org/), [GitHub](https://github.com/mmp/pbrt-v4) |
| LuxCoreRender | LuxCoreRender community | Apache 2.0 | Free | Open-source physically based renderer | [GitHub](https://github.com/LuxCoreRender/LuxCore) |

The commercial renderers (RenderMan, Arnold, V-Ray) are proven in film production, but they are closed and paid per seat or node, every year, so the cost grows with the size of the render farm and the studio cannot find out why a render breaks or add its own features. The open-source renderers (Cycles, pbrt-v4, LuxCoreRender) are free and readable under Apache 2.0, but the studio would depend on their communities for fixes, which the client found too slow, and none of them was built around the studio's pipeline. No existing solution gives the studio a renderer it owns, understands and can extend, which is why it wants its own.

## What is ray tracing?

Ray tracing is a rendering technique that uses mathematical equations to follow the path of light between the camera (the point of view) and the scene. In real life, light leaves a source and bounces from object to object before reaching our eyes; ray tracing does it backwards, casting ("tracing") rays from the camera into the scene and following them as they bounce off objects towards the lights, to produce an image. This simulates realistic lighting, with physically accurate shadows, reflections and indirect lighting: for example, a shadow is sharp near the point where the object touches the ground, and softer and wider further away. Many effects build on this idea, such as global illumination, reflections and translucency.

**Sources:**

- Where I started: [Unreal Engine — What is real-time ray tracing?](https://www.unrealengine.com/explainers/ray-tracing/what-is-real-time-ray-tracing)
- References I would go back to: [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html) and [Physically Based Rendering (pbrt)](https://pbrt.org/)

## What is C++?

C++ is a multi-paradigm language: procedural, object-oriented and generic. The first two look very similar to JavaScript, PHP and Python, but it has no garbage collector, so memory management needs more attention. In exchange, programs are very fast.

### Programming paradigms

- **Procedural programming:** functions and reusable blocks of code.
- **Object-oriented programming:** classes, objects, inheritance and encapsulation.
- **Generic programming:** templates that create reusable code for different data types, similar to TypeScript generics but more powerful.

Unlike JavaScript or Python, C++ is statically typed and compiled, which gives developers more control over memory and performance.

### What to watch out for

The main pitfalls are:

- **Uninitialised variables:** they can lead to unpredictable behaviour.
- **Array bounds:** accessing an invalid index can cause crashes or memory corruption.
- **Memory leaks:** allocated memory must be released properly.
- **Dangling pointers:** a pointer can refer to an object that no longer exists.
- **Compilation:** the code must be compiled before it runs, usually after each change.

Modern C++ provides RAII and smart pointers to make memory management safer.

### Shaping the domain model

For a 3D rendering project, I would split the domain into classes and simple data structures.

Classes, which have behaviour:

- **Camera:** position and viewing direction; creates a ray for each pixel of the image.
- **Sphere:** geometry and ray intersection.
- **Light:** light source properties.
- **Scene:** contains the objects, the lights and the camera.
- **Renderer:** generates the final image.

Simple data structures, which represent values:

- **Vector3:** 3D coordinates or directions (x, y, z).
- **Color:** RGB values.
- **Ray:** origin and direction.
- **Material:** colour, reflectivity and transparency.

Classes handle behaviour, while simple structures represent values.

**Sources:**

- Where I started: [LearnCpp](https://www.learncpp.com/) — C++ fundamentals and tutorials.
- References I would go back to: [cppreference](https://en.cppreference.com/) — C++ technical reference, and its [Object lifetime](https://en.cppreference.com/w/cpp/language/lifetime) page on memory and object lifetime.

# 5. Run the CI on GitHub Actions inside the dev container

## Context

Partner studios will contribute later. Every pull request must be built and tested automatically,
so a broken change is caught before it reaches `main`. The result must match what contributors
see locally: ADR 0001 makes the dev container the only supported environment.

Alternatives considered, and why they fit worse:

- **Install the tools directly on the CI runner** (`apt-get install cmake ...`): faster, but the
  compiler and versions would differ from the dev container, so the CI could pass while a
  contributor's build fails, or the reverse.
- **Push a prebuilt image to a registry and reuse it in CI:** faster runs, but needs a registry,
  credentials and a step to keep the image up to date; too much for a project this size.
- **GitLab CI, CircleCI or another external service:** the repository is on GitHub; another
  service means another account and another configuration to maintain.

Our reason: GitHub Actions is built into the platform we already use, and the `devcontainers/ci`
action builds `.devcontainer/` and runs our own `make test` inside it. The CI and every
contributor use the same image and the same command, so "it passes on my machine" means "it
passes in CI".

## Decision

A GitHub Actions workflow (`.github/workflows/ci.yml`) runs on every pull request and every push
to `main`. It builds the dev container with `devcontainers/ci` and runs `make test` inside it.

## Status

Accepted

## Consequences

- Every pull request shows whether the project builds and the tests pass, in the same environment
  as contributors.
- Changing `.devcontainer/` changes the CI too: there is only one environment to maintain.
- The image is rebuilt on each run, so the CI takes a few minutes; caching can be added later.
- Only the Linux build is tested: the native Windows presets are not covered by the CI.
- The CI depends on GitHub; free minutes are limited if the repository is private.

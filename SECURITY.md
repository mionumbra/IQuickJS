# Security Policy

## Reporting A Vulnerability

Do not report security vulnerabilities through public GitHub issues.

Use GitHub's private security advisory flow for this repository. If that is unavailable, contact the repository owner privately through GitHub with a description, reproduction steps, affected versions or commits, and any suggested mitigation.

Reports involving `iqjs_unsafe_*` APIs should identify whether the behavior occurs when those APIs are used with documented valid inputs. These APIs intentionally expose native pointer functionality and can crash or corrupt a process when misused.

## Supported Versions

Security fixes are applied to the latest commit on `main`. No released-version support policy exists yet.

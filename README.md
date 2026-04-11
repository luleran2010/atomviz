# How to compile

Use vcpkg to install the dependencies. The Magnum Engine in vcpkg is too old, use `--head` to obtain the latest version from github

```
vcpkg install eigen
vcpkg install imgui
vcpkg install --head corrade magnum
vcpkg install --head magnum-integration[imgui,eigen]
```

For tests:

```
vcpkg install catch2
```
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

# Problem with Eigen

When in build folder under `vcpkg_installed/x64-windows/include`, create a symbolic like of Eigen by (need administrative priviledge)
```
mklink /J Eigen eigen3/Eigen
```
so that Eigen can be found by other libraries.
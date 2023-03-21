# Asset Importer Rules - Native (CPP/Blueprints) Edition

This repo is an example of how you can use C++ and Blueprints to build an post-import asset pipeline.

## How to use

1. Clone the repo into a plugins folder, preferably at the Project level.
2. Enable the plugin in your `.uproject` file or through the plugin manager in unreal, it is called `Importer Rules`
   !(Documentation/importer.rules.plugin.menu.png)
3. Open Project Settings -> Post Import Asset Rules

### Example Rules

## Framework breakdown

`Rules` are made out of `Queries` and `Actions`

### Queries

### Actions

#### SetEditorProperties

This is the most generic included action. Pass in any editor properties as parameter values. For example, for a texture you might pass in:

```SetEditorProperties(srgb=True)```

The naming of the editor properties that are available for a given class can by found in the stub definition of the unreal class. For example:

```text
Texture 2D

**C++ Source:**

- **Module**: Engine
- **File**: Texture2D.h

**Editor Properties:** (see get_editor_property/set_editor_property)

- ``address_x`` (TextureAddress):  [Read-Write] Address X:
    The addressing mode to use for the X axis.
- ``address_y`` (TextureAddress):  [Read-Write] Address Y:
    The addressing mode to use for the Y axis.
- ``adjust_brightness`` (float):  [Read-Write] Adjust Brightness:
    Static texture brightness adjustment (scales HSV value.)  (Non-destructive; Requires texture source art to be available.)
```

This action will fail if the target does not have the given property name or if the value is the wrong type.

#### SetAssetTags

This action is for setting asset tags on import. It takes a dictionary of `str:Any` but be aware it runs `str()` on the value, so only types that can be cast to `str()` will be valid.

#### Making an action in Blueprints

### Rules

Rules are simple enough, they are just a set of `Queries` and a set of `Actions`. If any/all `Queries` pass then *all* `Actions` are run. If `requires_all` is True, then *all* `Queries` must pass, if False, then a *single* `Query` is enough to cause the actions to run.


## Notes


* This tutorial was made for `#notGDC 2023`! Check out some other great entries at [https://notgdc.io](https://notgdc.io)

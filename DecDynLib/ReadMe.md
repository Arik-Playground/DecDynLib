# DecDynLib

## Declarative Dynamic Libraries 

DecDynLib is a utility library that allows to load a library at run time and still keep the 'type-safty' that comes with compile time library linkage.

## Using the library

### Step 1 - Defining the library

first, you have to define the library exports, you can do it either with your library or a third party one
```
using namespace ddl::literals;
auto g_kernel32_map = ddl::make_exports_map(
	ddl::export_info<decltype(::CreateFileW)>("CreateFileW"_eid)
    ddl::export_info<bool>(123_eid)
);
```

lets  explain whats happening here line by line

> using namespace ddl::literals;

this line allows us to use the '_eid' literals which helps us create export ids

> auto g_kernel32_map = ddl::make_exports_map(

This is the declaration of the library map.
The library map is a special veriable that holds the exports information in its type definition.
this variable can be easly elided by the compiler.

> ddl::export_info<decltype(::CreateFileW)>("CreateFileW"_eid),

By adding this argument to the *'make_exports_map'* we are defining a new export
with the type of *decltype(::CreateFileW)* and it being accessed with the string "CreateFileW"

> ddl::export_info<bool>(123_eid)

This line adds a new export definition for a boolean variable that can be accessed with the ordinal 123.

### Step 2 - using the library definition
Using the export map from before is quite easy with platform libraries
#### Windows
Windows projects should be linked with the *win32lib* library, 
after that the usage is as follows:
```
	auto opt_kernel32 = ddl::win32::library(g_kernel32_map, "kernel32.dll");
	assert(opt_kernel32);
	auto& kernel32_ddl = *opt_kernel32;
	kernel32_ddl["CreateFileW"_eid](L"blabla", GENERIC_ALL, 0, nullptr, OPEN_EXISTING, 0, NULL);
```
The line
> auto opt_kernel32 = ddl::win32::library(g_kernel32_map, "kernel32.dll");

loads the library and assigning it the g_kernel32_map export map that we have defined before.

> assert(opt_kernel32);

ddl::win32::library returns an optional that can be checked for its validity

> auto& kernel32_ddl = *opt_kernel32;

this line extracts the library from the optional

> kernel32_ddl["CreateFileW"_eid](L"blabla", GENERIC_ALL, 0, nullptr, OPEN_EXISTING, 0, NULL);

And finally this line locates the desired function in the dll and returns a pointer with the expected type.
(the [] operator returns a pointer because std::optional doesn't allow optional refs).

#### Linux\POSIX
*Not supported yet*

## Dependencies
This libraries has no external dependencies although there is a possibilty where the tests will use externel testing library

## Author
- Me! (JK... Noam Arye Nassi)

## Important notes
Most of the code in this library uses tricks from Louis Dionne talks (Youtube is full of those),
The reason i'm not simply using hana in my library is to avoid dependencies.

## License
The author of this repo is not responsible for any result that comes from using the code in it.
feel free to use this code in your own projects, modify it or even marry it.
# leaf language spec


## Foreword
This is my first spec I have ever written. I am open to any feedback, especially on how to define
terms. I think there is some interesting ideas in here.


### Definitions


**expression**
A construct of code that gets evaluated. At this point of the language it is extremly difficult
to define exactly how expressions are made.

**statement**
Actions that make up a program. Each statement performs a specific task or operation, such as
assigning a value to a variable, performing a calculation, or controlling the flow of a programs
execution.

**result type**
The static type that an expression evaluates to.

**result value**
The runtime value that an expression evaluates to.



### Keywords

**abandon**
When used infront of a value this will cancel the destruction of that value. `abandon $foo`;

**discard**
Allows for unused values by writing `discard foo();`. Because everything is nodiscard by default
this is necessarry.

In this language there is multiple different things that can modify entities in various ways.
We split into a few categories:\
Attributes


### Operators


Single argument operators:

| Name        | Symbol  | Usecase                                                                                                     |     |
| ----------- | ------- | ----------------------------------------------------------------------------------------------------------- | --- |
| Relocate    | `$foo`  | Get the value of an identity                                                                                |     |
| Access      | `foo.`  | Access a member                                                                                             |     |
| Dereference | `foo->` | Pointer Access                                                                                              |     |
| [unamed]    | `@foo`  | Getting mutable access to an identity, when that identity gives a mutable place. Else gives a const access. |     |
| Address     | `&foo`  | Get the address of a place                                                                                  |     |


Double argument operators:

All of these have an identity or a value on either side. For exameple: `5 + 3`

`+` `-` `*` `/` `%` `=`  `:=` \
`+=` `-=` `*=` `/=` `%=`\
`<=` `>=` `<` `>` `==` 


Variadic argument operators:

| Name         | Symbol       | Usecase |     |
| ------------ | ------------ | ------- | --- |
| Parameter    | `(foo, bar)` |         |     |
| Array Access | `[foo, bar]` |         |     |

  
### Variable Declaration

```
// Syntax Sugar
Foo foo;
var Foo foo;
const Foo foo;
```

### Function Declaration
```
fn foo() -> Bar {}


fn foo(Foo foo) -> Bar {}
```


We want a $ operator for relocability. This operator will move the value at the place of the
identity `$x` into the expression, where it becomes a value.

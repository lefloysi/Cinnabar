# leaf language spec


## Foreword
This is my first spec I have ever written. I am open to any feedback, especially on how to define
terms. I think there is some interesting ideas in here.




### Definitions

**EKWAHI**\
Everyone knows what a horse is.\
This is used in cases where the definition is obvious

**Foo** and **Bar**\
Whenever you see these two it is meant as a placeholder.


**expression**\
A construct of code that gets evaluated. At this point of the language it is extremly difficult
to define exactly how expressions are made etc.



**result type**\
The static type that an expression evaluates to.

**result value**\
The runtime result of an expression.



### Keywords

**abandon**\
When used infront of a value this will cancel the destruction of that value. `abandon $foo`;

**discard**\
Allows for unused values by writing `discard foo();`. Because everything is nodiscard by default
this is necessarry.

In this language there is multiple different things that can modify entities in various ways.
We split into a few categories:\
Attributes


### Operators


Single argument operators:

| Name        | Symbol  | Usecase |
| ----------- | ------- | ------- |
| Relocate    | `$foo`  |         | 
| Access      | `foo.`  |         |
| Dereference | `foo->` |         |
| [unamed]    | `@foo`  | Getting mutable access to an identity, when that identity gives a mutable place. Else gives a const access. |
| Address     | `&foo`  |         |


Double argument operators:


Variadic argument operators:

| Name          | Symbol      | Usecase | 
| Addition      | `foo + bar` | EKWAHI |

### Variable Declaration
There is two syntaxes. The officially implemented one, and syntax sugar.
```
// Built in
var foo : Foo;
var foo : Foo = bar; // any kind of initializer

// Syntax Sugar
Foo foo;
Foo foo = bar;
```

### Function Declaration
```
fn foo() -> Bar {}


fn foo(Foo foo) -> Bar {}
```


We want a $ operator for relocability. This operator will move the value at the place of the
identity `$x` into the expression, where it becomes a value.

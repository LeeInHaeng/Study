console.log('Im Working. Im Javascript. Im worth it');
let a=221;
let b=a-5;
a=4;
const c=111;
//c=5;

///////// let, var difference ////////////
//// var ---> function-scope , hosting
    /*
    console.log(foo); // undefined
    var foo;
    
    var foo = 'bar1';
    var foo = 'bar2';
    */
////////////////////////////////////
//// let ---> block-scoped
    /*
    console.log(foo); // Error: Uncaught ReferenceError: foo is not defined
    let foo;
    
    let foo = 'bar1';
    let foo = 'bar2';
    // ERROR: Uncaught SyntaxError: Identifier 'foo' has already been declared
    */
////////////////////////////////////
console.log(b,a,c);
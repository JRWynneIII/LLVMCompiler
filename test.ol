EXTERN putchar(var c: char)
BEGIN main()
  var a: int
  let a = 0
  var c: char
  let c = 'h'
  label loopTop:
    call putchar(c) 
    let a = a + 1
    if a isnot 10
      goto loopTop
  1
END

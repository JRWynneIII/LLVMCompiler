EXTERN putchar(var c: char)

BEGIN putTen(var c: char)
  var a: int
  let a = 0
  for a to 10
    call putchar(c)
  next
  call putchar('\n')
  1
END

BEGIN main()
  var a: int
  let a = 0
  var c: char
  let c = 'h'
  for a to 10
    call putTen(c)
  next
  1
END

extern putchar(var c: char)

begin main()
  var outer: int
  var inner: int
  var inner2: int
  var limit: int
  let outer = 0
  let inner = 0
  let inner2 = 0
  let limit = 10
  for outer to limit
    call putchar('\n')
    let inner = 0
    for inner to limit
      let inner2 = 0
      for inner2 to limit
        call putchar('*')
      next
    next
  next
  1
end

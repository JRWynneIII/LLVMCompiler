extern putchar(var c:char)

begin main()
  var rows: int
  var spaces: int
  var star: int
  var number_of_stars: int
  let number_of_stars = 6
  var number_of_rows: int
  let number_of_stars = number_of_rows

  let rows = 0

  for rows to number_of_rows
    let spaces = 0
    for spaces to number_of_stars
      call putchar(' ')
    next
    let star = 1
    for star to rows
      call putchar('*')
      call putchar(' ')
    next
    call putchar('\n')
    let number_of_stars = number_of_stars - 1
  next
  1
end

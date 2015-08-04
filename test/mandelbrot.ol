extern putchar(var c: char)
extern rand()

begin main()
  var a: int
  var b: int
  var x: double
  var y: double
  var zi: double
  var zr: double
  var zni: double
  var znr: double
  var maxiter: int
  var iter: int
  var escapeval: int
  var sq: double
  let maxiter = 31
  let escapeval = 0
  let sq = 0.0
  let b = 0
  let x = 0.0
  let y = 0.0
  let zi = 0.0
  let zr = 0.0
  let zni = 0.0
  let znr = 0.0
  let iter = 0

  for b to 32
    let a = 0
    for a to 85
      let zi = 0.0
      let zr = 0.0
      let zni = 0.0
      let znr = 0.0
      let iter = 1
      let escapeval = 0

      let x = (a - 50.0) / 20.0
      let y = (b - 16.0) / 10.0
      for iter to 31
        let zni = 2.0 * zi * zr + y
        let znr = zr * zr - zi * zi + x
        let zi = zni
        let zr = znr
        let sq = zi * zi + zr * zr
        if sq < 4.0
          let escapeval = 1
      next
      if escapeval is 1
       call putchar('*')
      if escapeval isnot 1
        call putchar(' ')
      let escapeval = 0
    next
    call putchar('\n')
  next
  1
end

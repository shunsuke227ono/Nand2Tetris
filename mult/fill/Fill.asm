(LISTEN)
  @KBD
  D=M
  @PRESSED
  D;JNE //if D!=0 jump to PRESSED
  @NOT_PRESSED
  0;JMP
(PRESSED)
  @color
  M=-1
  @FILL_INI
  0;JMP
(NOT_PRESSED)
  @color
  M=0
  @FILL_INI
(FILL_INI)
  @SCREEN
  D=A
  @target_pixel
  M=D
  @pixel_counter
  M=0
  @FILL
  0;JMP
(FILL)
  @8192 // 32*256 total of pixels in screen
  D=A
  @pixel_counter
  D=D-M
  @LISTEN
  D;JLE
  @color
  D=M
  @target_pixel
  A=M // set A to value of M[target_pixel] 
      // M[target]の値をアドレスに持つものをcolorで染めたい
      // が、@Mのようにすると、Mが変数として判断されてしまう。
      // @~~と同じ意味を持つのが、A=~~であり、
      // Aをセットすることで、次以降でMによって、そのAの値を
      // アドレスに持つメモリにアクセスできてる。
  M=D // set M[M[target_pixel]] = M[color]
  @pixel_counter
  M=M+1
  @target_pixel
  M=M+1
  @FILL
  0;JMP

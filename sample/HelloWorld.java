public class HelloWorld {

  private int n = 18;

  public static int add2(int a, int b) { return a + b; }

  public int add3(int a, int b, int c) { return a + b + c; }

  public float fadd2(float a, float b) {
    return a + b;
  }

  public double dadd2(double a, double b) {
    return a + b;
  }

  public long ladd2(long a, long b) {
    return a + b;
  }

  public int getn() {
    return n;
  }

  public void setn(int a) {
    n = a;
  }

  public int recursive_sum(int a) {
    if (a == 0)
      return 0;
    return a + recursive_sum(a - 1);
  }

  public int loop_sum(int a) {
    int sum = 0;
    while(a>0) {
      sum += a;
      a -= 1;
    }
    return sum;
  }
}


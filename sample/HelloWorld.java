import de.inetsoftware.jwebassembly.api.annotation.Export;

public class HelloWorld {

    private int n = 18;

    @Export
    public static int add2(int a, int b) {
      return a+ b;
    }

    @Export
    public int add3(int a, int b, int c) {
      return a+b+c;
    }

    @Export
    public float fadd2(float a, float b) {
      return a + b;
    }

    @Export
    public double dadd2(double a, double b) {
      return a + b;
    }

    @Export
    public long ladd2(long a, long b) {
      return a + b;
    }

    @Export
    public int getn() {
      return n;
    }

    @Export
    public void setn(int a) {
      n = a;
    }
}


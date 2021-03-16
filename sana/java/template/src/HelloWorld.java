import de.inetsoftware.jwebassembly.api.annotation.Export;

public class HelloWorld {

    @Export
    public static int add2(int a, int b) {
      return a+ b;
    }

    @Export
    public int add3(int a, int b, int c) {
      return a+b+c;
    }
}


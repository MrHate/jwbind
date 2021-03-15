package jwbind.desc;

import java.util.List;

public class ClassDesc {

  public static class AttrEntry {
    public int name;
    public int global;
    public int flags;
  }

  public static class MethodEntry {
    public int name;
    public int func;
    public int flags;
  }

  public int className;
  public List<AttrEntry> attributes;
  public List<MethodEntry> methods;
  public List<String> stringRefs;
}

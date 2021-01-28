/*
  We are going to make a single dimensional array of integers.  
 */

class MrLine
{
 public:
  MrLine(int size=0);
  MrLine(const MrLine & other_line);
  MrLine & operator = (const MrLine & other_line);
  void clear();
  ~MrLine();
 private:
  void copy_line(const MrLine & other_line);
  int * the_line;
  int m_size;
};

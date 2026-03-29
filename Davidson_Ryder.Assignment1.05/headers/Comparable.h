class Comparable
{
public:
    virtual ~Comparable() {}

    virtual int compareTo(const Comparable &other) const = 0;
};
#ifndef AtomViz_Atom_h
#define AtomViz_Atom_h

#include <vector>
#include <Eigen/Dense>

class AtomInterface {
public:
    virtual ~AtomInterface() {}
    virtual Eigen::Vector3f position() const = 0;
    virtual Eigen::Vector3f velocity() const = 0;
    virtual Eigen::Vector3f force() const = 0;
    virtual int number() const = 0;
    virtual float mass() const {}
    virtual float charge() const {}
};

class Atom: public AtomInterface {
public:
    Atom() {}
    virtual ~Atom() {}

    virtual Eigen::Vector3f position() const override { return _position; }
    virtual void setPosition(const Eigen::Vector3f& position){ _position = position; }

    virtual Eigen::Vector3f velocity() const override { return _velocity; }
    virtual void setVelocity(const Eigen::Vector3f& velocity) { _velocity = velocity; }

    virtual Eigen::Vector3f force() const override { return _force; }
    virtual void setForce(const Eigen::Vector3f& force) { _force = force; }

    virtual int number() const override { return _number; }
    virtual void setNumber(int number) { _number = number; }

    virtual float mass() const { return _mass; }
    virtual float charge() const { return _charge; }
private:
    Eigen::Vector3f _position;
    Eigen::Vector3f _velocity;
    Eigen::Vector3f _force;
    int _number;
    float _mass;
    float _charge;
};

typedef Eigen::Matrix3f Cell;

struct Atoms {
public:
    class AtomRef : public AtomInterface {
    public:
        AtomRef(Atoms& atoms, int index) : _atoms(atoms), _index(index) {}
        virtual ~AtomRef() {}

        virtual Eigen::Vector3f position() const override { return _atoms[_index].position(); }
        virtual void setPosition(const Eigen::Vector3f& position) { _atoms[_index].setPosition(position); }

        virtual Eigen::Vector3f velocity() const override { return _atoms[_index].velocity(); }
        virtual void setVelocity(const Eigen::Vector3f& velocity) { _atoms[_index].setVelocity(velocity); }

        virtual Eigen::Vector3f force() const override { return _atoms[_index].force(); }
        virtual void setForce(const Eigen::Vector3f& force) { _atoms[_index].setForce(force); }

        virtual int number() const override { return _atoms[_index].number(); }
        virtual void setNumber(int number) { _atoms[_index].setNumber(number); }

        virtual float mass() const override { return _atoms[_index].mass(); }
        virtual float charge() const override { return _atoms[_index].charge(); }
    private:
        Atoms& _atoms;
        int _index;
    };

    class ConstAtomRef : public AtomInterface {
    public:
        ConstAtomRef(const Atoms& atoms, int index) : _atoms(atoms), _index(index) {}
        virtual ~ConstAtomRef() {}

        virtual Eigen::Vector3f position() const override { return _atoms[_index].position(); }

        virtual Eigen::Vector3f velocity() const override { return _atoms[_index].velocity(); }

        virtual Eigen::Vector3f force() const override { return _atoms[_index].force(); }

        virtual int number() const override { return _atoms[_index].number(); }

        virtual float mass() const override { return _atoms[_index].mass(); }
        virtual float charge() const override { return _atoms[_index].charge(); }
    private:
        const Atoms& _atoms;
        int _index;
    };

    Atoms() {}
    Atoms(const Cell& cell, const Eigen::MatrixX3f& positions, Eigen::ArrayXi numbers);
    Atoms(const Cell& cell, const std::vector<Atom>& atoms);

    size_t size() const { return _size; }

    Eigen::MatrixX3f positions() const { return _positions; }
    void setPositions(const Eigen::MatrixX3f& positions) { _positions = positions; }

    Eigen::MatrixX3f velocities() const { return _velocities; }
    void setVelocities(const Eigen::MatrixX3f& velocities) { _velocities = velocities; }

    Eigen::MatrixX3f forces() const { return _forces; }
    void setForces(const Eigen::MatrixX3f& forces) { _forces = forces; }

    Eigen::ArrayXi numbers() const { return _numbers; }
    void setNumbers(const Eigen::ArrayXi& numbers) { _numbers = numbers; }

    Eigen::ArrayXf masses() const { return _masses; }
    void setMasses(const Eigen::ArrayXf& masses) { _masses = masses; }

    Eigen::ArrayXf charges() const { return _charges; }
    void setCharges(const Eigen::ArrayXf& charges) { _charges = charges; }

    Cell cell() const { return _cell; }
    void setCell(const Cell& cell, bool wrap = true);

    Eigen::MatrixX3f fractionalPositions() const { return _positions * _cell.inverse(); }
    void setFractionalPositions(const Eigen::MatrixX3f& fractionalPositions) { _positions = fractionalPositions * _cell; }

    void wrapPositions() { _positions = (fractionalPositions() - fractionalPositions().array().floor().matrix()) * _cell; }

    AtomRef operator[](int index) { return AtomRef(*this, index); }
    ConstAtomRef operator[](int index) const { return ConstAtomRef(*this, index); }
private:
    size_t _size;

    Eigen::MatrixX3f _positions;
    Eigen::MatrixX3f _velocities;
    Eigen::MatrixX3f _forces;
    Eigen::ArrayXi _numbers;
    Eigen::ArrayXf _masses;
    Eigen::ArrayXf _charges;

    Cell _cell;
};

#endif
#ifndef AtomViz_Atom_h
#define AtomViz_Atom_h

#include <vector>
#include <Eigen/Dense>

#include "typedefs.h"

class AtomInterface {
public:
    virtual ~AtomInterface() {}
    virtual Eigen::Vector3f position() const = 0;
    virtual Eigen::Vector3f velocity() const = 0;
    virtual Eigen::Vector3f force() const = 0;
    virtual int number() const = 0;
    virtual float mass() const = 0;
    virtual float charge() const  = 0;
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

class Atoms {
public:
    class AtomRef : public AtomInterface {
    public:
        AtomRef(Atoms& atoms, int index):
            _atoms(atoms), _index(index),
            _position{_atoms._positions.block<1, 3>(index, 0)},
            _velocity{_atoms._velocities.block<1, 3>(index, 0)},
            _force{_atoms._forces.block<1, 3>(index, 0)},
            _number{_atoms._numbers(index)},
            _mass{_atoms._masses(index)},
            _charge{_atoms._charges(index)}
            {}
        virtual ~AtomRef() {}

        virtual int index() const { return _index; }

        virtual Eigen::Vector3f position() const override { return _position.transpose(); }
        virtual void setPosition(const Eigen::Vector3f& position) { _position = position.transpose(); }

        virtual Eigen::Vector3f velocity() const override { return _velocity.transpose(); }
        virtual void setVelocity(const Eigen::Vector3f& velocity) { _velocity = velocity.transpose(); }

        virtual Eigen::Vector3f force() const override { return _force.transpose(); }
        virtual void setForce(const Eigen::Vector3f& force) { _force = force.transpose(); }

        virtual int number() const override { return _number; }
        virtual void setNumber(int number) { _number = number; }

        virtual float mass() const override { return _mass; }
        virtual float charge() const override { return _charge; }
    private:
        Atoms& _atoms;
        int _index;
        Eigen::Block<Eigen::MatrixX3f, 1, 3> _position;
        Eigen::Block<Eigen::MatrixX3f, 1, 3> _velocity;
        Eigen::Block<Eigen::MatrixX3f, 1, 3> _force;
        int& _number;
        float& _mass;
        float& _charge;
    };

    class ConstAtomRef : public AtomInterface {
    public:
        ConstAtomRef(const Atoms& atoms, int index):
            _atoms(atoms), _index(index),
            _position{_atoms._positions.block<1, 3>(index, 0)},
            _velocity{_atoms._velocities.block<1, 3>(index, 0)},
            _force{_atoms._forces.block<1, 3>(index, 0)},
            _number{_atoms._numbers(index)},
            _mass{_atoms._masses(index)},
            _charge{_atoms._charges(index)}
            {}
        virtual ~ConstAtomRef() {}

        virtual Eigen::Vector3f position() const override { return _position.transpose(); }

        virtual Eigen::Vector3f velocity() const override { return _velocity.transpose(); }

        virtual Eigen::Vector3f force() const override { return _force.transpose(); }

        virtual int number() const override { return _number; }

        virtual float mass() const override { return _mass; }

        virtual float charge() const override { return _charge; }
    private:
    private:
    private:
        const Atoms& _atoms;
        int _index;
        const Eigen::Block<const Eigen::MatrixX3f, 1, 3> _position;
        const Eigen::Block<const Eigen::MatrixX3f, 1, 3> _velocity;
        const Eigen::Block<const Eigen::MatrixX3f, 1, 3> _force;
        int _number;
        float _mass;
        float _charge;
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
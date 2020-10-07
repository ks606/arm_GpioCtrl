#ifndef MYGPIOCTRL_H_
#define MYGPIOCTRL_H_

enum dirEnum {
    DIR_IN,
    DIR_OUT,
};


class C_GpioCtrl{
    private:
        int m_num;
        dirEnum m_dir;

        bool exportGpio();
        bool unexportGpio();
        bool directionGpio();
        bool setGpio(char);
    protected:
        int m_fd;

    public:
        C_GpioCtrl( int, dirEnum );       
        ~C_GpioCtrl();

        bool set0();
        bool set1();
};



#endif /* MYGPIOCTRL_H_ */
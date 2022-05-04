#include <dlfcn.h>
#include <iostream>

int main(int argc, char ** argv)
{
	int data1=3;
	int data2=5;

	int valeur1;
	int valeur2;

    void *handle1;
    void *handle2;
    char *error;

    handle1 = dlopen("libComposant1.so", RTLD_LAZY);
    handle2 = dlopen("libComposant2.so", RTLD_LAZY);
    if (!handle1 || !handle2) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    dlerror();

    int (*composant1)(int, int);
    int (*composant2)(int, int);
    *(void **) (&composant1) = dlsym(handle1, "composant1");
    *(void **) (&composant2) = dlsym(handle2, "composant2");

    if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }

    valeur1 = (*composant1)(data1,data2);
    valeur2 = (*composant2)(data1,data2);
    std::cout << "valeur 1 :" << valeur1 << " valeur 2 :" << valeur2 << std::endl;

    dlclose(handle1);
    dlclose(handle2);
    exit(EXIT_SUCCESS);
}

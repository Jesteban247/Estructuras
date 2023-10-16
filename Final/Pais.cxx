
class Pais
{
    private:
        int id;
        string continente;
        string nombre;
        int estado;

    public:
        Pais(int id, string continente, string nombre)
        {
            this->id = id;
            this->continente = continente;
            this->nombre = nombre;
            this->estado = 0;
        }

        int getId()
        {
            return id;
        }

        string getContinente()
        {
            return continente;
        }

        string getNombre()
        {
            return nombre;
        }

        int getEstado()
        {
            return estado;
        }

        void setEstado(int estado)
        {
            this->estado = estado;
        }
};

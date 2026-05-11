void dibujarTablero() {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLS; j++) {
            float x = MARGEN + j * TAM_CASILLA;
            float y = MARGEN + i * TAM_CASILLA;
            float z = 0.0f;

            bool esCasillaClara = (i + j) % 2 == 0;
            if (j > 4) esCasillaClara = !esCasillaClara;

            if (casillaOscila[i][j]) {
                if (faseClaraOscura) {
                    glColor3f(0.5f, 0.5f, 1.0f);
                }
                else {
                    glColor3f(0.1f, 0.1f, 0.5f);
                }
            }
            else {
                if (esCasillaClara)
                    glColor3f(1.0f, 1.0f, 1.0f);
                else
                    glColor3f(0.0f, 0.0f, 0.0f);
            }

            glBegin(GL_QUADS);
            glVertex3f(x, y, z);
            glVertex3f(x + TAM_CASILLA, y, z);
            glVertex3f(x + TAM_CASILLA, y + TAM_CASILLA, z);
            glVertex3f(x, y + TAM_CASILLA, z);
            glEnd();

            if (esPuntoPoder(i, j))
                dibujarCruz(x, y, z);
        }
    }
}

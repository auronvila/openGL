    #shader vertex
    #version 120

    attribute vec3 aPos;

    void main()
    {
        gl_Position = vec4(aPos, 1.0);
    }


    #shader fragment
    #version 120

    uniform vec4 u_Color;

    void main()
    {
        gl_FragColor = u_Color;
    }

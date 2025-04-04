    #shader vertex
    #version 120

    attribute vec3 aPos;

    void main()
    {
        gl_Position = vec4(aPos, 1.0);
    }


    #shader fragment
    #version 120

    void main()
    {
        gl_FragColor = vec4(0.2, 2.0, 0.0, 1.0);
    }

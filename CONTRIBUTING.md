# Contributing

## Pull requests
Do not make pull requests on the `dist/` folder. This output will be overwritten. Instead, create a pull request for the source file(s) in `efm2riot/`

## Templates
In `efm2riot/templates/`, the template files exist. [Jinja2](http://jinja.pocoo.org/) is used for converting templates to source.

### Whitespace control
The output of the source files *has* to be 'beautiful'. This means that whitespaces and newlines should be controlled explicitly. This can be hard while preserving readability of the source files.

The two problems are solved by the `{% strip n, s %}{% endstrip %}` tag. The parameter `n` strips `n` times four spaces from all resulting lines. The `s` parameter is optional. When it is equal to `<` or `>`, it will remove one redundant whitespace before or after the block when the block renders empty.

#### Without `strip` block

```c
// Some other code

{% if condition %}
    /**
     * @brief   Define for enabling Advanced Energy Monitor core output via SWO.
     */
    #define AEM_ENABLED
{% endif %}

// Some other code
```

If condition is true, the above block would render as:

```c
// Some other code

    /**
     * @brief   Define for enabling Advanced Energy Monitor core output via SWO.
     */
    #define AEM_ENABLED

// Some other code
```

Or, if condition is false:

```c
// Some other code


// Some other code
```

#### With `strip` block

```c
// Some other code

{% strip 2, ">" %}
    {% if condition %}
        /**
         * @brief   Define for enabling Advanced Energy Monitor core output via SWO.
         */
        #define AEM_ENABLED
    {% endif %}
{% endstrip %}

// Some other code
```

If condition is true, the above block would render as:

```c
// Some other code

/**
 * @brief   Define for enabling Advanced Energy Monitor core output via SWO.
 */
#define AEM_ENABLED

// Some other code
```

Or, if condition is false:

```c
// Some other code

// Some other code
```

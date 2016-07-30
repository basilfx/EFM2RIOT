def only_for_board(boards):
    """
    Create a filter that is only considered when the given board matches.
    """

    def inner(context):
        return context["board"] in boards
    return inner



define(['require','jquery','react','classnames','keyCode','css!ReactComponentsBase/Dropdown/Dropdown'],function (require) {
  

  var $ = require('jquery');
  var React = require('react');
  var classNames = require('classnames');
  var KeyCode = require('keyCode');

  require('css!ReactComponentsBase/Dropdown/Dropdown');

  /**
   * Makes a dropdown component with a "button" (the clickable part) and a "menu" (the
   * hidden part). Useful for hiding many actions within a single element. Also useful
   * more generally as a "click here to show" type element.
   *
   * Usage:
   *   <Dropdown buttonContent=[content of the button] [other attributes]>
   *     [content of the menu]
   *   </Dropdown>
   *
   * Should more or less adhere to the WAI-ARIA best practices, but there may be missing
   * functionality. See http://www.w3.org/WAI/PF/aria-practices/#menu for more.
   *
   * FIXME (tzhang): I have yet to come up with a good way to implement the ability to
   * traverse the menu with arrow keys while still maintaining the flexibility of
   * containing any sort of contents.
   */
  var Dropdown = React.createClass({
    displayName: 'Dropdown',

    /* ****************** React class setup stuff **************** */
    propTypes: {
      // Optional "base class", for styling overrides.
      // Ie, instead of "Dropdown-menu", use "[baseClass]-menu"
      baseClass: React.PropTypes.string,

      // Optional classes for the button
      buttonClasses: React.PropTypes.string,

      // The default content to display in the button
      buttonContent: React.PropTypes.node.isRequired,

      // Children elements
      children: React.PropTypes.node,

      // function to call on a key down event.
      fnOnKeyDown: React.PropTypes.func,

      // Whether or not the dropdown is disabled (default: enabled)
      // Adds a 'disabled' class to the wrapperClasses and the buttonClasses
      isDisabled: React.PropTypes.bool,

      // Menu will use fixed instead of absolute positioning
      isMenuPositionFixed: React.PropTypes.bool,

      // Optional classes for the menu
      menuClasses: React.PropTypes.string,

      // Callback to call after dropdown is hidden
      onMenuHiddenCallback: React.PropTypes.func,

      // Callback to call after dropdown is shown
      onMenuShownCallback: React.PropTypes.func,

      // Optional classes for the wrapping div
      wrapperClasses: React.PropTypes.string
    },

    getDefaultProps: function getDefaultProps() {
      return {
        baseClass: 'Dropdown',
        isDisabled: false,
        onMenuHiddenCallback: $.noop,
        onMenuShownCallback: $.noop,
        isMenuPositionFixed: false
      };
    },

    getInitialState: function getInitialState() {
      return {
        // Whether the menu is hidden
        menuHidden: true
      };
    },

    /* ************* React lifecycle binding functions *********** */
    componentDidMount: function componentDidMount() {
      $(document.body).on('click touchstart keydown', this._globalHideHandler);
    },

    componentDidUpdate: function componentDidUpdate(prevProps, prevState) {
      // If the menu is transitioning to hidden
      if (!prevState.menuHidden && this.state.menuHidden) {
        this.props.onMenuHiddenCallback();
      }

      // If the menu is transitioning to shown
      if (prevState.menuHidden && !this.state.menuHidden) {
        this.props.onMenuShownCallback(this);
      }
    },

    componentWillUnmount: function componentWillUnmount() {
      // FIXME (tzhang): Should onMenuHiddenCallback() be invoked here?
      $(document.body).off('click touchstart keydown', this._globalHideHandler);
    },

    /* ********************* Public functions ******************** */
    /**
     * Hide the menu part of the dropdown
     */
    hideMenu: function hideMenu() {
      this.setState({
        menuHidden: true
      });
    },

    /**
     * Show the menu part of the dropdown
     */
    showMenu: function showMenu() {
      this.setState({
        menuHidden: false
      });
    },

    getMenuElement: function getMenuElement() {
      return this.refs.dropdownMenu;
    },

    /* ******************** Private functions ******************** */
    /**
     * Handle the click event on the button; toggles the menu
     *
     * @param e: the React keyDown event
     */
    _clickHandler: function _clickHandler(e) {
      e.stopPropagation();

      if (!this.props.isDisabled) {
        this._toggleMenu();
      }
    },

    /**
     * Event handler to hide the menu when clicking or hitting enter or space outside the
     * dropdown element.
     *
     * @param e: the React event that is being handled
     */
    _globalHideHandler: function _globalHideHandler(e) {
      var $eventTarget = $(e.target);
      var dropdownElement = this.refs.dropdownWrapper;
      if (!$eventTarget.closest(dropdownElement).length && (e.type === 'click' || e.which === KeyCode.ENTER || e.which === KeyCode.SPACE)) {
        this.hideMenu();
      }
    },

    /**
     * Handle the keydown event on the button. Toggles the menu on enter or space; hides
     * it on escape.
     *
     * @param e: the React keyDown event
     */
    _keydownHandler: function _keydownHandler(e) {
      e.stopPropagation();

      switch (e.which) {
        case KeyCode.DOWN:
          this.showMenu();
          break;
        case KeyCode.ENTER:
          e.preventDefault();
        case KeyCode.SPACE:
          this._toggleMenu();
          break;
        case KeyCode.ESCAPE:
        case KeyCode.TAB:
          this.hideMenu();
      }

      if (this.props.fnOnKeyDown && !this.state.menuHidden) {
        this.props.fnOnKeyDown(e);
      }
    },

    /**
     * Toggle the visibility of the menu part of the dropdown
     */
    _toggleMenu: function _toggleMenu() {
      this.setState({
        menuHidden: !this.state.menuHidden
      });
    },

    render: function render() {
      var baseClass = this.props.baseClass;

      var wrapperClasses = classNames(baseClass, this.props.wrapperClasses, {
        disabled: this.props.isDisabled,
        opened: !this.state.menuHidden
      });
      var buttonClasses = classNames(baseClass + '-button', this.props.buttonClasses, { disabled: this.props.isDisabled });

      var menuClassMap = {};
      menuClassMap[baseClass + '-hidden'] = this.state.menuHidden;
      menuClassMap[baseClass + '-fixed'] = this.props.isMenuPositionFixed;
      if (this.props.menuClasses) {
        menuClassMap[this.props.menuClasses] = true;
      }
      var menuClasses = classNames(baseClass + '-menu', menuClassMap);

      return React.createElement(
        'div',
        {
          ref: 'dropdownWrapper',
          className: wrapperClasses
        },
        React.createElement(
          'div',
          {
            ref: 'dropdownButton',
            onClick: this._clickHandler,
            onKeyDown: this._keydownHandler,
            disabled: this.props.isDisabled,
            role: 'menubar',
            'aria-haspopup': 'true',
            'aria-expanded': !this.state.menuHidden,
            tabIndex: '0',
            className: buttonClasses
          },
          this.props.buttonContent
        ),
        React.createElement(
          'div',
          {
            ref: 'dropdownMenu',
            role: 'menu',
            'aria-hidden': this.state.menuHidden,
            tabIndex: '-1' // Do not let the menu container accept focus
            , className: menuClasses
          },
          this.props.children
        )
      );
    }
  });

  return Dropdown;
});
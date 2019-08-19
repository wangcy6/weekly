

var _extends = Object.assign || function (target) { for (var i = 1; i < arguments.length; i++) { var source = arguments[i]; for (var key in source) { if (Object.prototype.hasOwnProperty.call(source, key)) { target[key] = source[key]; } } } return target; };

/**
 * Copyright 2015-2016 Evernote Corporation. All rights reserved.
 *
 * Utility for adding dragging and dropping to existing React components.
 */
define(['require','react','react-dom','lodash','jquery','keyCode','SimplePortal','css!EvernoteDragUtil'],function (require) {
  

  var React = require('react');
  var ReactDOM = require('react-dom');
  var _ = require('lodash');
  var $ = require('jquery');
  var KeyCode = require('keyCode');
  var SimplePortal = require('SimplePortal');
  require('css!EvernoteDragUtil');

  // States of the drag system state machine and each drag component when rendered
  var DRAG_STATE = {
    NORMAL: 'normal', // Nothing is being dragged
    START: 'start', // Mouse down but drag threshold not reached
    DRAGGING: 'dragging' // Something is being dragged
  };

  var ACTIVE_DRAG_CONTAINER_CLASS = 'EvernoteDragUtil-active-drag-container';

  // The number of pixels that the mouse needs to be dragged for something to be picked up
  var DRAG_START_THRESHOLD = 3;

  // The state of the drag system
  var dragItemState = DRAG_STATE.NORMAL;

  /**
   * Mouse coords for current location, start location, and location within
   * dragging element
   */
  var mouseClientX = 0;
  var mouseClientY = 0;
  var mouseDragStartClientX = 0;
  var mouseDragStartClientY = 0;
  var mouseNodeOffsetX = 0;
  var mouseNodeOffsetY = 0;

  // Current drag component subscribed to updates
  var dragComponent = null;

  // Current drag item (passed to create drop descriptor)
  var dragItem = null;

  // Current filtering function to let drag items only interact with certain drop items
  var fnDropItemFilter = null;

  // Current drop descriptor function to describe what happens on drop
  var fnGetDropDescriptor = null;

  // Current callback for dropping the item
  var fnOnDrop = null;

  // Current drop descriptor passed addProps() for hover styling and to the drop handler
  var dropDescriptor = {};

  /**
   * Drop area components subscribed to drop descriptor changes and with a rectangle for
   * checking intersection with the dragging component
   */
  var dropAreaComponents = [];

  // The current dropItem being hovered over
  var mouseHoverDropAreaItem = {};

  /**
   * Called on mousedown of drag component to:
   *   - begin watching for drag threshold
   *   - register the dragItem and dropDescriptor getter
   *   - subscribe drag component to dragItemState, mouse movements, and dropDescriptor
   */
  function startDrag(dragItemData) {
    dragItemState = DRAG_STATE.START;
    dragComponent = dragItemData.dragComponent;
    mouseNodeOffsetX = dragItemData.mouseNodeOffsetX;
    mouseNodeOffsetY = dragItemData.mouseNodeOffsetY;
    mouseDragStartClientX = dragItemData.mouseDragStartClientX;
    mouseDragStartClientY = dragItemData.mouseDragStartClientY;
    dragItem = dragItemData.dragItem;
    fnDropItemFilter = dragItemData.fnDropItemFilter;
    fnGetDropDescriptor = dragItemData.fnGetDropDescriptor;
    fnOnDrop = dragItemData.fnOnDrop;

    // Attach mousemove and mouseup listeners to window
    window.addEventListener('mousemove', handleMouseMove);
    window.addEventListener('mouseup', handleMouseUp, true);
    window.addEventListener('keyup', handleKeyUp);
  }

  /**
   * Called on mouseup while in START or DRAGGING state to:
   *  - deregister dragItem and dropDescriptor getter
   *  - unsubscribe the drag component to drag state and mouse coord changes
   *
   * Note: the mouseup handler is responsible for invoking the onDrop callback
   */
  function endDrag() {
    dragItemState = DRAG_STATE.NORMAL;

    dragComponent.setState({
      dragState: {},
      dropDescriptor: {}
    });
    dragComponent = null;
    dragItem = null;
    fnGetDropDescriptor = null;
    fnOnDrop = null;
    mouseHoverDropAreaItem = null;
    dropDescriptor = {};

    updateAllSubscribedToDropDescriptor();

    // Detach mousemove and mouseup listeners to window
    window.removeEventListener('mousemove', handleMouseMove);
    window.removeEventListener('mouseup', handleMouseUp, true);
    window.removeEventListener('keyup', handleKeyUp);
  }

  /**
   * Drop areas register themselves on mounting to subscribe to dropDescriptor and
   * provide a client rectangle and dropItem that can be hovered over
   */
  function registerDropAreaComponent(c) {
    dropAreaComponents.push(c);
  }

  /**
   * Drop areas deregister themselves on unmounting
   */
  function unregisterDropAreaComponent(c) {
    _.pull(dropAreaComponents, c);
  }

  /**
   * The dragComponent is subscribed to updates in dragItemState and mouse coordinates
   */
  function updateDragComponentState() {
    dragComponent.setState({
      dragState: {
        dragItemState: dragItemState,
        mouseClientX: mouseClientX,
        mouseClientY: mouseClientY,
        mouseDragStartClientX: mouseDragStartClientX,
        mouseDragStartClientY: mouseDragStartClientY,
        mouseNodeOffsetX: mouseNodeOffsetX,
        mouseNodeOffsetY: mouseNodeOffsetY
      }
    });
  }

  /**
   * Drop areas and the drag component are subscribed to the dropDescriptor. This should
   * be called whenever the dropDescriptor changes to update those subscribed.
   */
  function updateAllSubscribedToDropDescriptor() {
    _.forEach(dropAreaComponents, function (c) {
      c.setState({
        dropDescriptor: dropDescriptor
      });
    });
    if (dragComponent) {
      dragComponent.setState({
        dropDescriptor: dropDescriptor
      });
    }
  }

  /**
   * Mousemove handler attached to window on NORMAL to START state transition. Handles:
   *   - updating the mouse coords
   *   - when state is START, checking distance threshold to transition to DRAGGING
   *   - when state is DRAGGING, updating the dropDescriptor since hovered areas may
   *     have changed
   */
  function handleMouseMove(e) {
    mouseClientX = e.clientX;
    mouseClientY = e.clientY;

    if (dragItemState === DRAG_STATE.START) {
      var dx = mouseClientX - mouseDragStartClientX;
      var dy = mouseClientY - mouseDragStartClientY;
      if (dx * dx + dy * dy >= DRAG_START_THRESHOLD * DRAG_START_THRESHOLD) {
        dragItemState = DRAG_STATE.DRAGGING;
      }
    } else if (dragItemState === DRAG_STATE.DRAGGING) {
      // When DRAGGING, update the drop descriptor on moving the mosue
      updateDropDescriptor();
      updateDragComponentState();
    }

    // Always update the drag component state since mouse coords changed
    updateDragComponentState();
  }

  /**
   * Mouseup handler attached to window on NORMAL to START state transition. Handles:
   *   - updating the mouse coords
   *   - when state is START, checking distance threshold to transition to DRAGGING
   *   - when state is DRAGGING, updating the dropDescriptor since hovered areas may
   *     have changed
   */
  function handleMouseUp() {
    if (dragItemState === DRAG_STATE.DRAGGING) {
      fnOnDrop(dropDescriptor);
    }
    endDrag();
  }

  /**
   * Keyup handler attached to window on NORMAL to START state transition. If the user
   * presses escape while dragging, then cancel the drag.
   */
  function handleKeyUp(e) {
    if (e.keyCode === KeyCode.ESCAPE) {
      endDrag();
    }
  }

  /**
   * The drop descriptor needs to be updated whenever the user might have dragged over
   * a different element. This loops through the registered dropAreaComponents to check
   * if they are being dragged over. If a new element is being dragged over, then we
   * update the drop descriptor by invoking the function that the user passed in.
   */
  function updateDropDescriptor() {
    var nextHoverDropAreaItem = null;
    var hoverRectSize = null;

    _.forEach(dropAreaComponents, function (c) {
      // Filter drop items that do not apply
      var dropItem = c.getDropItem();
      if (fnDropItemFilter(dropItem)) {
        // Check if the mouse is inside of it
        var rect = c.getBoundingRectangle();
        if (rect && mouseClientY > rect.top && mouseClientY < rect.bottom && mouseClientX > rect.left && mouseClientX < rect.right) {
          // If the area is smaller than the existing hover drop area, then do that one
          var rectSize = rect.width * rect.height;
          if (hoverRectSize === null || rectSize < hoverRectSize) {
            // Make sure this drop area is not inside of a current drag area
            if (!c.isInsideActiveDragItem()) {
              nextHoverDropAreaItem = dropItem;
              hoverRectSize = rectSize;
            }
          }
        }
      }
    });

    // If the currently dragged-over dropItem has changed, update the drop descriptor
    if (!_.isEqual(nextHoverDropAreaItem, mouseHoverDropAreaItem)) {
      mouseHoverDropAreaItem = nextHoverDropAreaItem;
      dropDescriptor = fnGetDropDescriptor(dragItem, mouseHoverDropAreaItem);
      updateAllSubscribedToDropDescriptor();
    }
  }

  /**
   * Exported function for wrapping a React component in a component that is draggable.
   * An instance of the returned component can be picked up by dragging more than the
   * DRAG_START_THRESHOLD. A ghosted instance of the wrapped component is rendered in
   * its ordinary location (which preserves the html flow) and a new, fixed-position
   * drag instance is rendered at the location that the user has dragged to.
   */
  var createDragClass = function createDragClass(userConfig) {
    // Don't bind the react class, otherwise react v15 refuses to instantiate it.
    var WrappedClass = userConfig.reactClass;
    var config = _.bindAll(_.defaults(userConfig, {
      reactClass: null,
      getDragItem: null,
      isDraggable: _.constant(true),
      dropItemFilter: _.constant(false),
      draggingOffsetX: _.constant(0),
      draggingOffsetY: _.constant(0),
      getHandleClassName: null,
      getDropDescriptor: null,
      addProps: _.noop,
      onDrop: null,
      ghostOpacity: 0.25
    }));

    // TODO validate the config object and make nice errors

    // Return the new React Class of the Drag component
    return React.createClass({
      getInitialState: function getInitialState() {
        return {
          dragState: {},
          dropDescriptor: {}
        };
      },

      componentWillUnmount: function componentWillUnmount() {
        if (this.state.dragState.dragItemState === DRAG_STATE.DRAGGING || this.state.dragState.dragItemState === DRAG_STATE.START) {
          endDrag();
        }
      },

      isElementInHandleArea: function isElementInHandleArea(el) {
        return !config.getHandleClassName || !!$(el).closest('.' + config.getHandleClassName(this.props)).length;
      },

      handleMouseDown: function handleMouseDown(e) {
        // Start the drag
        if (dragItemState === DRAG_STATE.NORMAL && config.isDraggable(this.props) && this.isElementInHandleArea(e.target)) {
          var rect = this.refs.dragSource.getBoundingClientRect();

          startDrag({
            dragComponent: this,
            mouseDragStartClientX: e.clientX,
            mouseDragStartClientY: e.clientY,
            mouseNodeOffsetX: e.clientX - rect.left - config.draggingOffsetX(this.props),
            mouseNodeOffsetY: e.clientY - rect.top - config.draggingOffsetY(this.props),
            dragItem: config.getDragItem(this.props),
            fnDropItemFilter: _.partialRight(config.dropItemFilter, this.props),
            fnGetDropDescriptor: config.getDropDescriptor,
            fnOnDrop: _.partialRight(config.onDrop, this.props)
          });
        }
      },

      render: function render() {
        var dragState = this.state.dragState;

        if (dragState.dragItemState === DRAG_STATE.DRAGGING) {
          // Ghost element is the same as a normal element except with a lower opacity
          var ghostStyle = {
            opacity: config.ghostOpacity
          };

          // Dragging element has a fixed position where the mouse has moved
          var posY = dragState.mouseClientY - dragState.mouseNodeOffsetY;
          var posX = dragState.mouseClientX - dragState.mouseNodeOffsetX;
          var dragStyle = {
            position: 'fixed',
            margin: 0,
            padding: 0,
            top: posY,
            left: posX,
            zIndex: 205,
            pointerEvents: 'none'
          };

          return React.createElement(
            'div',
            { key: 'dragContainer', className: ACTIVE_DRAG_CONTAINER_CLASS },
            React.createElement(
              'div',
              { key: 'ghost', style: ghostStyle },
              React.createElement(WrappedClass, _extends({}, this.props, config.addProps(DRAG_STATE.NORMAL, dropDescriptor, this.props)))
            ),
            React.createElement(
              SimplePortal,
              null,
              React.createElement(
                'div',
                { key: 'dragSource', style: dragStyle, ref: 'dragSource' },
                React.createElement(WrappedClass, _extends({}, this.props, config.addProps(DRAG_STATE.DRAGGING, dropDescriptor, this.props)))
              ),
              React.createElement('div', { className: 'EvernoteDragUtil-clickLayer' })
            )
          );
        } else {
          // Not in DRAGGING state, so render normal element with event handlers
          return React.createElement(
            'div',
            { key: 'dragContainer' },
            React.createElement(
              'div',
              { key: 'dragSource', ref: 'dragSource', onMouseDown: this.handleMouseDown },
              React.createElement(WrappedClass, _extends({}, this.props, config.addProps(DRAG_STATE.NORMAL, dropDescriptor, this.props)))
            )
          );
        }
      }
    });
  };

  /**
   * Exported function for wrapping a React component in one that is a drop area. An
   * instance of the returned component can be dragged over and the user-defined dropItem
   * will be used to identify what the component represents.
   */
  var createDropAreaClass = function createDropAreaClass(userConfig) {
    // Don't bind the react class, otherwise react v15 refuses to instantiate it.
    var WrappedClass = userConfig.reactClass;
    var config = _.bindAll(_.defaults(userConfig, {
      propTypes: {},
      reactClass: null,
      addProps: _.noop
    }));

    // TODO validate the config object and make nice errors

    return React.createClass({
      propTypes: config.propTypes,

      getInitialState: function getInitialState() {
        return {
          dropDescriptor: {}
        };
      },

      componentDidMount: function componentDidMount() {
        registerDropAreaComponent(this);
      },

      componentWillUnmount: function componentWillUnmount() {
        unregisterDropAreaComponent(this);
      },

      isInsideActiveDragItem: function isInsideActiveDragItem() {
        var node = ReactDOM.findDOMNode(this.refs.dropArea);
        return !!$(node).closest('.' + ACTIVE_DRAG_CONTAINER_CLASS).length;
      },

      getBoundingRectangle: function getBoundingRectangle() {
        // Should this be memoized? How would we detect changes on updates or scroll?
        return ReactDOM.findDOMNode(this.refs.dropArea).getBoundingClientRect();
      },

      getDropItem: function getDropItem() {
        return config.getDropItem(this.props);
      },

      render: function render() {
        return React.createElement(WrappedClass, _extends({
          ref: 'dropArea'
        }, this.props, config.addProps(this.getDropItem(), this.state.dropDescriptor, this.props)));
      }
    });
  };

  return {
    DRAG_STATE: DRAG_STATE,
    createDragClass: createDragClass,
    createDropAreaClass: createDropAreaClass
  };
});